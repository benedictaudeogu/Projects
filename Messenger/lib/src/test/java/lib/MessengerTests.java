package lib;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import com.messenger.User;

class MessengerTests {

	@BeforeEach
	void setUp() throws Exception {}

	@Test
	void testUserCreation() {
		String expectedName = "Benedicta";
		User user = new User(expectedName);
		assertEquals(user.getName(), expectedName);
	}
}