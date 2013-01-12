
class SerialReader {
public:
	int available() {
		return Serial.available();
	}

	char * readCommand() {
		char cmd[20];
		int i=0;
		while(Serial.available()) {
			char data = Serial.read();
			cmd[i]=data;
			if (data == '\n') break;
			i++;
		}
		cmd[i] = 0;
		return strdup(cmd);
	}

	void print(char data) {
		Serial.print(data);
	}

	void println(char data) {
		Serial.println(data);
	}

	void print(char* data) {
		Serial.print(data);
	}

	void println(char* data) {
		Serial.print(data);
	}

	void println(int data, int type) {
		Serial.println(data, type);
	}
};

