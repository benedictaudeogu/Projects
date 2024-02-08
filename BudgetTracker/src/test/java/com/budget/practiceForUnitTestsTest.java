package com.budget;

import static org.junit.Assert.assertEquals;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class practiceForUnitTestsTest {
	practiceForUnitTests practice;
	
	@BeforeEach
	public void setUp() {
		practice = new practiceForUnitTests();
	}
	
	@Test
	public void twoPlusTwoIsFour() {
		assertEquals(4, practice.add(2, 2));
	}
	
	@Test
	public void threePlusSevenIsTen() {
		assertEquals(10, practice.add(3, 7));
	}
	
	
	@Test
	public void FiftyNineIsF() {
		assertEquals('F', practice.determineLetterGrade(59));
	}
	
	@Test
	public void sixtyNineIsD() {
		assertEquals('D', practice.determineLetterGrade(69));
	}
	
	@Test
	public void seventyNineIsC() {
		assertEquals('C', practice.determineLetterGrade(79));
	}
	
	@Test
	public void eightyNineIsB() {
		assertEquals('B', practice.determineLetterGrade(89));
	}
	
	@Test
	public void ninetyNineIsA() {
		assertEquals('A', practice.determineLetterGrade(99));
	}

}
