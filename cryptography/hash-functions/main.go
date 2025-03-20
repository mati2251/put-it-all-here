package main

import (
	"crypto/md5"
	"crypto/sha1"
	"crypto/sha256"
	"crypto/sha512"
	"fmt"
	"golang.org/x/crypto/sha3"
	"hash"
	"math/bits"
	"math/rand"
	"os"
	"sort"
	"time"
)

var md5h hash.Hash
var sha1h hash.Hash
var sha256h hash.Hash
var sha224h hash.Hash
var sha512h hash.Hash
var sha384h hash.Hash
var sha3_224h hash.Hash
var sha3_256h hash.Hash
var sha3_384h hash.Hash
var sha3_512h hash.Hash

var hashFuncs = map[string]hash.Hash{}

func initHash() {
	md5h = md5.New()
	sha1h = sha1.New()
	sha256h = sha256.New()
	sha512h = sha512.New()
	sha3_224h = sha3.New224()
  sha3_256h = sha3.New256()
  sha3_384h = sha3.New384()
  sha3_512h = sha3.New512()
	sha224h = sha256.New224()
	sha384h = sha512.New384()
	hashFuncs["md5"] = md5h
	hashFuncs["sha1"] = sha1h
	hashFuncs["sha2-256"] = sha256h
	hashFuncs["sha2-224"] = sha224h
	hashFuncs["sha2-512"] = sha512h
	hashFuncs["sha2-384"] = sha384h
  hashFuncs["sha3-224"] = sha3_224h
  hashFuncs["sha3-256"] = sha3_256h
  hashFuncs["sha3-384"] = sha3_384h
	hashFuncs["sha3-512"] = sha3_512h 
	var err error
	resultFile, err = os.Create("result.csv")
	check(err)
}

var resultFile *os.File

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func addScore(score map[string]string) {
	var keys []string
	for k := range score {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	var result string
	for _, k := range keys {
		result += score[k] + ", "
	}
	resultFile.WriteString(result + "\n")
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

func userInput() {
	var input string
	fmt.Println("Enter the string to hash:")
	fmt.Scanln(&input)
	for k, v := range hashFuncs {
		v.Write([]byte(input))
		hashLabel := v.Sum(nil)
		v.Reset()
		fmt.Printf("%s: %x\n", k, hashLabel)
	}
}

func speedTest() {
	fmt.Println("Speed test:")
	files := readFiles()
	for _, file := range files {
		scores := map[string]string{}
		stats, err := file.Stat()
		check(err)
		content := make([]byte, stats.Size())
		_, err = file.Read(content)
		check(err)
		fmt.Printf("File: %s\n", stats.Name())
		for k, v := range hashFuncs {
			startTime := time.Now()
			v.Write(content)
			v.Sum(nil)
			stopTime := time.Since(startTime)
			v.Reset()
			fmt.Printf("%s: %v\n", k, stopTime)
			scores[k] = stopTime.String()
		}
		addScore(scores)
	}
}

func randomString(size int) string {
	letters := []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
	b := make([]rune, size)
	for i := range b {
		b[i] = letters[rand.Intn(len(letters))]
	}
	return string(b)
}

func findCollision(method hash.Hash, to int, wordsCount int) {
	var strings = make(map[string]bool)
	for len(strings) != wordsCount {
		strings[randomString(4)] = true
	}

	var duplicates = make(map[string]int)
	for k := range strings {
		method.Write([]byte(k))
		hash := method.Sum(nil)
		method.Reset()
		partHash := string(hash[:to])
		if _, ok := duplicates[partHash]; ok {
			duplicates[partHash]++
		} else {
			duplicates[partHash] = 0
		}
	}
	fmt.Printf("Collisions: %d\n", wordsCount-len(duplicates))
}

func shortMD5Test() {
	input := randomString(10)
	fmt.Println("Short MD5 test:")
	fmt.Printf("Input: %s\n", input)
	md5h.Write([]byte(input))
	fmt.Printf("MD5: %x\n", md5h.Sum(nil))
	md5h.Reset()
	input = "Microsoft"
	fmt.Printf("Input: %s\n", input)
	md5h.Write([]byte(input))
	fmt.Printf("MD5: %x\n", md5h.Sum(nil))
	md5h.Reset()
}

func sacTest() {
	input := []byte(randomString(100))
	fmt.Println("SAC test:")
	for k, v := range hashFuncs {
		fmt.Printf("%s: ", k)
		v.Write(input)
		orginal := v.Sum(nil)
		v.Reset()
		input[10] = input[10] ^ 1
		v.Write(input)
		modified := v.Sum(nil)
		v.Reset()
		fmt.Printf("Original: %x\n", orginal)
		fmt.Printf("Modified: %x\n", modified)
		diff := 0
		for i := 0; i < len(orginal); i++ {
			diff += bits.OnesCount8(orginal[i] ^ modified[i])
		}
		fmt.Printf("Changed bits %d%%\n", (100 * diff / (len(orginal) * 8)))
	}
}

func main() {
	initHash()
	userInput()
	speedTest()
	shortMD5Test()
	findCollision(sha3_224h, 2, 250)
	sacTest()
}
