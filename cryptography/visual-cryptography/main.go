package main

import (
	"crypto/rand"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"math/big"
	"os"
)

func decodeImage(filename string) (image.Image, error) {
	f, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	img, _, err := image.Decode(f)
	return img, err
}

func encodeImage(filename string, img image.Image) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	err = png.Encode(f, img)
	return err
}

func setPixels(part *image.RGBA, pixelsValue []int, x int, y int) error {
	if len(pixelsValue) != 4 {
		return fmt.Errorf("pixelsValue must have 4 values")
	}
	x = x * 2
	y = y * 2
	part.Set(x, y, color.RGBA{uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), 255})
	part.Set(x+1, y, color.RGBA{uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), 255})
	part.Set(x, y+1, color.RGBA{uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), 255})
	part.Set(x+1, y+1, color.RGBA{uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), uint8(pixelsValue[0] * 255), 255})
	return nil
}

var pixels = [][]int{
	{0, 0, 1, 1},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{1, 0, 0, 1},
	{1, 0, 1, 0},
	{1, 1, 0, 0},
}

func generateWhitePixel(x int, y int, partOne *image.RGBA, partTwo *image.RGBA) {
	to := big.NewInt(6)
	optionNum, err := rand.Int(rand.Reader, to)
	if err != nil {
		fmt.Println("Error generating random number")
		return
	}
	setPixels(partOne, pixels[optionNum.Int64()], x, y)
	setPixels(partTwo, pixels[optionNum.Int64()], x, y)
}

func generateBlackPixel(x int, y int, partOne *image.RGBA, partTwo *image.RGBA) {
	to := big.NewInt(6)
	optionNum, err := rand.Int(rand.Reader, to)
	if err != nil {
		fmt.Println("Error generating random number")
		return
	}
	setPixels(partOne, pixels[optionNum.Int64()], x, y)
	setPixels(partTwo, pixels[optionNum.Int64()], x, y)
	opositePixels := make([]int, 4)
	for i, pixel := range pixels[optionNum.Int64()] {
		opositePixels[i] = 1 - pixel
	}
	setPixels(partTwo, opositePixels, x, y)
}

func encode(filename string) error {
	img, err := decodeImage(filename)
	if err != nil {
		fmt.Println("Error decoding image")
		return err
	}
	partOne := image.NewRGBA(image.Rect(0, 0, img.Bounds().Dx()*2, img.Bounds().Dy()*2))
	partTwo := image.NewRGBA(image.Rect(0, 0, img.Bounds().Dx()*2, img.Bounds().Dy()*2))
	for y := 0; y < img.Bounds().Dy(); y++ {
		for x := 0; x < img.Bounds().Dx(); x++ {
			r, g, b, _ := img.At(x, y).RGBA()
			gray := r>>8 + g>>8 + b>>8/3
			isBlack := gray < 128
			if isBlack {
				generateBlackPixel(x, y, partOne, partTwo)
			} else {
				generateWhitePixel(x, y, partOne, partTwo)
			}
		}
	}
	err = encodeImage("part_one.png", partOne)
	if err != nil {
		fmt.Println("Error encoding image")
		fmt.Println(err.Error())
	}
	err = encodeImage("part_two.png", partTwo)
	if err != nil {
		fmt.Println("Error encoding image")
		fmt.Println(err.Error())
	}
	return err
}

func decode(filename1 string, filename2 string) {
	partOne, err := decodeImage(filename1)
	if err != nil {
		fmt.Println("Error decoding image")
	}
	partTwo, err := decodeImage(filename2)
	if err != nil {
		fmt.Println("Error decoding image")
	}
	if partOne.Bounds().Dx() != partTwo.Bounds().Dx() || partOne.Bounds().Dy() != partTwo.Bounds().Dy() {
		fmt.Println("Images must have the same size")
		return
	}
	newImage := image.NewRGBA(image.Rect(0, 0, partOne.Bounds().Dx(), partOne.Bounds().Dy()))
	for y := 0; y < partOne.Bounds().Dy(); y++ {
		for x := 0; x < partOne.Bounds().Dx(); x++ {
			r1, _, _, _ := partOne.At(x, y).RGBA()
			r2, _, _, _ := partTwo.At(x, y).RGBA()
			r1 = r1>>8 + r2>>8/2
			newImage.Set(x, y, color.RGBA{uint8(r1), uint8(r1), uint8(r1), 255})
		}
	}
  err = encodeImage("decoded.png", newImage)
}

func main() {
	if len(os.Args) == 2 {
		encode(os.Args[1])
	} else if len(os.Args) == 3 {
    decode(os.Args[1], os.Args[2])
	} else {
		fmt.Printf("Usage: %s <image_path>", os.Args[0])
		fmt.Printf("Usage: %s <part_first> <part_second>", os.Args[0])
		return
	}
}
