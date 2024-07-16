.PHONY: all clean desktop web run-web

all: desktop

desktop:
	@mkdir -p build/desktop
	@cd build/desktop && cmake ../.. && cmake --build .

web:
	@mkdir -p build/web
	@cd build/web && emcmake cmake ../.. && emmake make

run-web:
	@cd build/web && python3 -m http.server

clean:
	@rm -rf build/desktop
	@rm -rf build/web
