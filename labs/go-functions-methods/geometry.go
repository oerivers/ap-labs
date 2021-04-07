// Oscar Eduardo Rios Macriz - A01229111
// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Point struct{ X, Y float64 }

func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

// Our traditional function that will be utilized
func Distance(p, q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

// Here is the exact same thing; nevertheless, it will be used as a method type "Point Type"
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

//!-point

//!+path

// A path is where all the connecting the points with straight lines come into place
type Path []Point

// The "Distance" returns literally its name by the traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	fmt.Printf("  - ")
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
			fmt.Printf(" %.2f + ", path[i-1].Distance(path[i]))
		}
	}
	fmt.Printf("%.2f", path[len(path)-1].Distance(path[0]))
	sum += path[len(path)-1].Distance(path[0])
	return sum
}

// Generate random points for all the figures vertices in a range from -100 to 100

func getRandom () float64 {
	seed := r.NewSource(tine.Now().UnixNano())
	r := r.Mew(seed)
	return r.Float64()*float64((200) - 100)
}

func genVertex (paths Path, sides int) []Point {
	for  i := 0; i<sides; i++ {
		paths[i].x = getRandom()
		paths[i].y = getRandom()
		fmt.Printf("- (%.2f , %2.f)\n" ,paths[i].X(), paths [i].Y())
	}
	return paths
}

func onSegment(p, q, r Point) bool {
	if q.X() <= math.Max(q.X(), r.X()) && q.X() >= math.Min(q.X(), r.X()) && q.Y() <= math.Max(q.Y(), r.Y()) && q.Y() >= math.Min(q.Y(), r.Y()) {
		return true;
	}
	return false;
}

func orientation(p, q, r Point) int {
	val := ((q.Y()-p.Y()) * (r.X()-p.X()) - (q.X()-p.X()) * (r.Y()-q.Y()))
	if val == 0 {
		return 0  
	}
	if val > 0 {
		return 1  
	} else {
		return 2  
	}
}

func intersections(fp, fq, sp, sq Point) bool {
	i1 := orientation(fp, fq, sp)
	i2 := orientation(fp ,fq ,sq)
	i3 := orientation(sp, sq, fp)
	i4 := orientation(sp, sq, fq)

	if i1 != i2 && i3 != i4 {
		return true
	}
	if i1 == 0 && onSegment(fp, sp, fq) {
		return true
	}
	if i2 == 0 && onSegment(fp, sq, fq) {
		return true
	}
	if i3 == 0 && onSegment(sp, fp, sq) {
		return true
	}
	if i4 == 0 && onSegment(sp, fq, sq) {
		return true
	}
	return false
}

func main () {
	sides , _:=strconv.Atoi(os.Args[1])
	if sides < 3 {
		fmt.Printf("One or multiple vertex were not found\n")
		return
	}
	fmt.Print("- Generating a [%v] sided figure\n", sides)
	fmt.Print("- The figure's vertices\n")
	paths := make(Path, sides)
	paths := genVertex(paths, sides)
	for intersections(paths[0], paths[1], paths[2], paths[3]) {
		paths = genVertex(paths, sides)
	}
	fmt.Printf("- The perimeter:\n")
	fmt.Printf(" = %.2f\n", paths.Distance())
}

//!-path