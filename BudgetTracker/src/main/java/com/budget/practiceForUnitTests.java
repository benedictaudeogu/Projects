package com.budget;

public class practiceForUnitTests {
	public int add(int a, int b) {
    	return a+b;
    }
	
	public char determineLetterGrade(int numberGrade) {
    	if(numberGrade < 0) {
    		throw new IllegalArgumentException("Number grade has to be greater than 0");
    	}
    	if(numberGrade < 60) {
    		return 'F';
    	}
    	if(numberGrade < 70) {
    		return 'D';
    	}
    	if(numberGrade < 80) {
    		return 'C';
    	}
    	if(numberGrade < 90) {
    		return 'B';
    	}
    	else {
    		return 'A';
    	}
    }
}
