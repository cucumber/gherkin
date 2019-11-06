package gherkin

import (
	"testing"
)

func TestIdGeneratorIncrementing(t *testing.T) {
	newId := Incrementing{}.NewId

	generated := newId()
	if generated != "0" {
		t.Errorf("Expected 0, got: %s", generated)
	}

	generated = newId()
	if generated != "1" {
		t.Errorf("Expected 1, got: %s", generated)
	}
}
