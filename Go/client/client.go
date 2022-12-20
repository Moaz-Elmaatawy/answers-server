package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"net/http"
	"time"
)
func readQuestions(inputFile string) string{
	file, err := ioutil.ReadFile(inputFile)
	if err != nil {
		fmt.Printf("Could not read the file due to this %s error \n", err)
	}

	fileContent := string(file)

	return fileContent
}
func main() {
	answersString :=[]byte(readQuestions("questions.txt"))
	
    c := http.Client{Timeout: time.Duration(1) * time.Second}
	for i:=0 ;  i< 10000 ; i++ {
		id:=i 
		j:=5
		for id != 0{
			answersString[j] = byte(id%10 + '0')
			id=id/10
			j--
		}
		answers := bytes.NewBuffer(answersString)
    	c.Post("http://localhost:8080", "/", answers)
	}
    fmt.Println("send ")
}