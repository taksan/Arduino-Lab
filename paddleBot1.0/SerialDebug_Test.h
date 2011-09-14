class SerialDebug {
public:
	static void println(const char * fmt, ...) 
	{
		va_list args;
		va_start(args, fmt);
		char msg[80];
		vsprintf(msg, fmt, args);
		va_end(args);

		printf("%s\n", msg);
	}
};

