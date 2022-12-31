package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"strconv"
	"math/rand"
	"sync"
)

var count=0
var studentAnswer map[int]string
const MAX_STUDENTS= 100000
var mux = sync.Mutex{}

func handle (w http.ResponseWriter, r *http.Request){

	defer r.Body.Close()

	body, err := io.ReadAll(r.Body)
	if err != nil {
		log.Fatalln(err)
	}

	packetNum,_ := strconv.Atoi(string(body[0:6]))

	mux.Lock()
	studentAnswer[(packetNum + rand.Intn(MAX_STUDENTS))%MAX_STUDENTS] = string(body)
	mux.Unlock()

	count+=1
	if count% 10000 == 0 {
		fmt.Println(count)
	}	
}
func main() {
	studentAnswer =  make(map[int]string)
	fmt.Println("Server Started")

	http.HandleFunc("/", handle)
    http.ListenAndServe(":8080", nil)
}