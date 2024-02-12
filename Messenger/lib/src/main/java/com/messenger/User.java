package com.messenger;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;

public class User {
	private String name;
	private String timestamp;

	public User(String Name) {
		this.setName(Name);
		this.setTimestamp(new SimpleDateFormat("MM.dd.yyyy HH:mm:ss").format(new Timestamp(System.currentTimeMillis())));
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getTimestamp() {
		return timestamp;
	}

	public void setTimestamp(String timestamp) {
		this.timestamp = timestamp;
	}

	@Override
	public String toString() {
		return "User [name= " + name + ", timestamp= " + timestamp + "]";
	}
}
