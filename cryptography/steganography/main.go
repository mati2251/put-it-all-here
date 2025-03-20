package main

import (
	"fmt"
	"image"
	"image/color"
	"image/png"
	"os"
	"strconv"
)

func decodeImage(filename string) (image.Image, error) {
	f, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	img, _, err := image.Decode(f)
	return img, err
}

func decode(filename string) {
	length_bits := 32
	img, err := decodeImage(filename)
	if err != nil {
		fmt.Println(err)
		return
	}
	bounds := img.Bounds()
	size := uint32(0)
	rgba := []uint32{0, 0, 0, 0}
	for i := 0; i < length_bits; i++ {
		current := i % 3
		if current == 0 {
			y := (i / 3) / bounds.Max.X
			x := (i / 3) % bounds.Max.X
			rgba[0], rgba[1], rgba[2], rgba[3] = img.At(x, y).RGBA()
		}
    size = size << 1
		size = size | (rgba[current] & 1)
	}
	content := make([]byte, size)
	for i := length_bits; i < int(size)+length_bits; i++ {
		current := i % 3
		if current == 0 {
			y := (i / 3) / bounds.Max.X
			x := (i / 3) % bounds.Max.X
			rgba[0], rgba[1], rgba[2], rgba[3] = img.At(x, y).RGBA()
		}
		rgba[current] >>= 8
		content[(i-length_bits)/8] <<= 1
		content[(i-length_bits)/8] |= (byte(rgba[current]) & 1)
	}
	fmt.Println(string(content))
}

func encode(filename string, messageFileName string, output string) {
	img, err := decodeImage(filename)
	if err != nil {
		fmt.Println(err)
		return
	}
	file, err := os.ReadFile(messageFileName)
	bits := fmt.Sprintf("%08b", file)
	bits = bits[1 : len(bits)-1]
	for i := 9; i < len(bits); i += 8 {
		bits = bits[:i-1] + bits[i:]
	}
	if err != nil {
		fmt.Println(err)
		return
	}
	size := len(bits)
	sizeBits := fmt.Sprintf("%032b", size)
	bits = sizeBits + bits
	size = len(bits)
	new_img := image.NewRGBA(img.Bounds())
	bounds := img.Bounds()
	image.NewRGBA(bounds)
	for y := bounds.Min.Y; y < bounds.Max.Y; y++ {
		for x := bounds.Min.X; x < bounds.Max.X; x++ {
			new_img.Set(x, y, img.At(x, y))
		}
	}
	rgba := []uint32{0, 0, 0, 0}
	for i := 0; i < size; i++ {
		current := i % 3
		if current == 0 {
			if i != 0 {
				y := ((i - 1) / 3) / bounds.Max.X
				x := ((i - 1) / 3) % bounds.Max.X
				color := color.RGBA{uint8(rgba[0]), uint8(rgba[1]), uint8(rgba[2]), uint8(rgba[3])}
				new_img.Set(x, y, color)
			}
			x := (i / 3) % bounds.Max.X
			y := (i / 3) / bounds.Max.X
			rgba[0], rgba[1], rgba[2], rgba[3] = img.At(x, y).RGBA()
		}
		bit, _ := strconv.Atoi(bits[i : i+1])
		rgba[current] = ((rgba[current] >> 8) & 254) | uint32(bit)
	}
	f, err := os.Create(output)
	if err != nil {
		fmt.Println(err)
		return
	}
	err = png.Encode(f, new_img)
	if err != nil {
		fmt.Println(err)
		return
	}
}

func printHelp(){
		fmt.Printf("Usage: %s decode/encode <input_file> args\n", os.Args[0])
		fmt.Printf("Decode: %s decode <input_file> \n", os.Args[0])
		fmt.Printf("Encode: %s encode <input_file> <input_message_file> <output_file>\n", os.Args[0])
}

func main() {
	if len(os.Args) < 3 {
    printHelp()
		return
	}
	mode := os.Args[1]
	if mode == "decode" {
		decode(os.Args[2])
	} else if mode == "encode" {
    if len(os.Args) < 5 {
      printHelp()
      return
    }
		encode(os.Args[2], os.Args[3], os.Args[4])
	} else {
		fmt.Println("Invalid mode")
		os.Exit(1)
	}

}
