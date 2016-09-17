 #ifndef ___ARDUINO__H___MOCK___
 #define ___ARDUINO__H___MOCK___
 #include <stdint.h>
 #include <stdio.h>

typedef bool boolean;

class SerialClass {
public:
 	void println(const char* s) {
		printf("%s\n", s);
	}
};

extern SerialClass Serial;

int millis();
#endif
