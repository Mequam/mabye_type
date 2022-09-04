timeouttype: main.cc
	g++ main.cc -o timeouttype
install: timeouttype
	chmod +x timeouttype
	sudo mv timeouttype /bin
uninstall:
	sudo rm /bin/timeouttype
clean:
	rm timeouttype
