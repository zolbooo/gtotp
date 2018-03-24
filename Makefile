TARGET = libtotp.a
FLAGS = --std=c++11

$(TARGET): totp.o sha1-hmac.o b32.o
	ar rcs $@ $^
	rm -f *.o

totp.o: totp.cpp totp.hpp
	g++ $(FLAGS) -c -o $@ $<

sha1-hmac.o: sha1-hmac.cpp sha1-hmac.hpp
	g++ $(FLAGS) -c -o $@ $<

b32.o: b32.cpp b32.hpp
	g++ $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)