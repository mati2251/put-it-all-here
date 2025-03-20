package main

import (
	"crypto/aes"
	"crypto/cipher"
	"fmt"
	"os"
	"strings"
	"time"
)

var resultFile *os.File

func check(e error) {
	if e != nil {
		panic(e)
	}
}

var iv []byte
var key []byte
var c cipher.Block


const (
	ecb = "ECB"
	cbc = "CBC"
	ofb = "OFB"
	cfb = "CFB"
	ctr = "CTR"
)

var modes = [5]string{ecb, cbc, ofb, cfb, ctr}

func initValues() {
  iv = []byte("1234567890123456")
  key = []byte("1234567890123456")
	resultFile, _ = os.Create("results.csv")
  var err error
  c, err = aes.NewCipher(key)
  check(err)
}

func getStream(cipherMode string, encrypter bool) cipher.Stream {
	switch cipherMode {
	case ofb:
		return cipher.NewOFB(c, iv)
	case cfb:
		if encrypter {
			return cipher.NewCFBEncrypter(c, iv)
		}
		return cipher.NewCFBDecrypter(c, iv)
	case ctr:
		return cipher.NewCTR(c, iv)
	}
	return nil
}

func encrypt(content []byte, mode string) []byte {
	c, err := aes.NewCipher(key)
	encryptedText := make([]byte, len(content))
	check(err)
	switch mode {
	case ecb:
		return ecbEncryption(content)
	case cbc:
		cipher.NewCBCEncrypter(c, iv).CryptBlocks(encryptedText, content)
		return encryptedText
	default:
		stream := getStream(mode, true)
		stream.XORKeyStream(encryptedText, content)
		return encryptedText
	}
}

func decrypt(content []byte, mode string) []byte {
	c, err := aes.NewCipher(key)
	check(err)
	decryptedText := make([]byte, len(content))
	switch mode {
	case ecb:
		return ecbDecryption(content)
	case cbc:
		cipher.NewCBCDecrypter(c, iv).CryptBlocks(decryptedText, content)
		return decryptedText
	default:
		stream := getStream(mode, false)
		stream.XORKeyStream(decryptedText, content)
		return decryptedText
	}
}

func addScore(score []string) {
  scoreStr := strings.Join(score, ",")
	resultFile.WriteString(scoreStr + "\n")
}

func readFiles() []*os.File {
	fileNames := []string{"random_file_1MB.txt", "random_file_10MB.txt", "random_file_100MB.txt", "random_file_1GB.txt"}
	files := make([]*os.File, len(fileNames))
	for index, fileName := range fileNames {
		file, err := os.Open(fileName)
		check(err)
		files[index] = file
	}
	return files
}

func timeEncryptionComparison() {
  fmt.Println("Time encryption comparison")
	files := readFiles()

	for _, file := range files {
		stats, err := file.Stat()
		check(err)
		fmt.Printf("File: %s, Size: %d bytes\n", stats.Name(), stats.Size())
		content := make([]byte, stats.Size())
		_, err = file.Read(content)
		check(err)
    score := make([]string, 10)
    
    for i, mode := range modes {
        fmt.Printf("%s mode\n", mode)
      	startTime := time.Now()
        encrypt(content, mode)
        encryptionTime := time.Since(startTime)
        fmt.Printf("Time to encrypt %s: %s\n", mode, encryptionTime)
        score[i] = encryptionTime.String()
        startTime = time.Now()
        decrypt(content, mode)
        decryptionTime := time.Since(startTime)
        score[i+5] = decryptionTime.String()
        fmt.Printf("Time to decrypt %s: %s\n", mode, decryptionTime)
    }
    addScore(score)
	}
	fmt.Printf("\n")
}

func errorPropagationComprasion() {
	fmt.Println("Error propagation")
  for _, mode := range modes {
    fmt.Printf("%s mode\n", mode)
    content := []byte("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla odio tortor, finibus eu purus laoreet, blandit ultricies elit. Donec maximus ligula ac posuere mollis. Vestibulum in lacus sed turpis viverra aliquet. Proin mollis purus nec semper dictum nunc.")
    goodCipherText := encrypt(content, mode)
    err := os.WriteFile("errors/good_encrypted_" + mode + ".txt", goodCipherText, 0644)
    check(err)
    err = os.WriteFile("errors/good_decrypted_" + mode + ".txt", content, 0644)
    check(err)
    content[36] = byte(20)
    badCipherText := encrypt(content, mode)
    err = os.WriteFile("errors/bad_encrypted_" + mode + ".txt", badCipherText, 0644)
    fmt.Printf("Good encryption: %s\n", goodCipherText)
    fmt.Printf("Bad encryption: %s\n", badCipherText)
    check(err)
    goodCipherText[36] = goodCipherText[36] + 1
    decrypted := decrypt(goodCipherText, mode)
    err = os.WriteFile("errors/bad_decrypted_" + mode + ".txt", decrypted, 0644)
    check(err)
    fmt.Printf("Bad decryption: %s\n", decrypted)
    fmt.Printf("Valid decryption: %s\n", string(content))
  }
  fmt.Printf("\n")
}

func ecbEncryption(content []byte) []byte {
	encrypted := make([]byte, len(content))
	blockSize := 16
	for bs, be := 0, blockSize; 0 < len(content); bs, be = bs+blockSize, be+blockSize {
		c.Encrypt(encrypted[bs:be], content[:blockSize])
		content = content[blockSize:]
	}
	return encrypted
}

func ecbDecryption(content []byte) []byte {
	decrypted := make([]byte, len(content))
	blockSize := 16
	for bs, be := 0, blockSize; 0 < len(content); bs, be = bs+blockSize, be+blockSize {
    c.Decrypt(decrypted[bs:be], content[:blockSize])
		content = content[blockSize:]
	}
	return decrypted
}

func cbcFromECB() {
	fmt.Println("CBC from ECB")
	block, err := aes.NewCipher([]byte("1234567890123456"))
	check(err)
	iv := []byte("1234567890123456")
	content := []byte("Lorem ipsum dolor sit amet, consectetur lit")
	encrypted := cbcEncryption(block, iv, content)
	fmt.Printf("CBC: %08b\n", encrypted)
	decrypted := cbcDecryption(block, iv, encrypted)
	fmt.Printf("Decrypted: %s\n", string(decrypted))
}

func cbcEncryption(block cipher.Block, iv []byte, content []byte) []byte {
  paddingSize := 16 - len(content)%16
  padding := make([]byte, paddingSize)
  for i := 0; i < paddingSize; i++ {
    if i == 0 {
      padding[i] = byte(1)
    } else if i != paddingSize-1 {
      padding[i] = byte(0)
    }  else {
      padding[i] = byte(paddingSize)
    }
  }
  content = append(content, padding...)
	encrypted := make([]byte, len(content))
	blockSize := 16
	for bs, be := 0, blockSize; bs < len(content); bs, be = bs+blockSize, be+blockSize {
		block.Encrypt(encrypted[bs:be], content[bs:be])
		for i := 0; i < blockSize; i++ {
			content[bs+i] ^= iv[i]
		}
		copy(iv, encrypted[bs:be])
	}
	return encrypted
}

func cbcDecryption(block cipher.Block, iv []byte, content []byte) []byte {
	decrypted := make([]byte, len(content))
	blockSize := 16
	for bs, be := 0, blockSize; bs < len(content); bs, be = bs+blockSize, be+blockSize {
		block.Decrypt(decrypted[bs:be], content[bs:be])
		copy(iv, content[bs:be])
	}
  if paddingValidation(decrypted) {
    decrypted = decrypted[:len(decrypted)-int(decrypted[len(decrypted)-1])]
  }
	return decrypted
}

func paddingValidation(content []byte) bool {
  padding := int(content[len(content)-1])
  for i := 0; i < padding - 2; i++ {
    if content[len(content)-2-i] != byte(0) {
      return false
    }
  }
  if content[len(content)-padding] != byte(1) {
    return false
  }
  return true
}

func main() {
  initValues()

  timeEncryptionComparison()

	errorPropagationComprasion()

	cbcFromECB()
}
