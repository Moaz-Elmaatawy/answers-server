package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"strconv"
)

func main() {
    http.HandleFunc("/", func (w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Welcome to my website!")

		defer r.Body.Close()

		b, err := io.ReadAll(r.Body)
		if err != nil {
			log.Fatalln(err)
		}
		packetNum,_ := strconv.Atoi(string(b[0:6]))
		if packetNum% 1000 == 0 {
			fmt.Println(packetNum)
		}
		
    })


    http.ListenAndServe(":8080", nil)
}