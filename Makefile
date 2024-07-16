.PHONY: all clean desktop web run-web

all: desktop

desktop:
	@if [ ! -d "build/desktop" ]; then $(MAKE) configure-desktop; fi
	@cd build/desktop && cmake --build .

web:
	@if [ ! -d "build/web" ]; then $(MAKE) configure-web; fi
	@cd build/web && emmake make

configure-with-address-sanitizer:
	@mkdir -p build/desktop
	@cd build/desktop && cmake -DUSE_ASAN=ON ../..

configure-with-memory-sanitizer:
	@mkdir -p build/desktop
	@cd build/desktop && cmake -DUSE_MSAN=ON ../..

configure-desktop:
	@mkdir -p build/desktop
	@cd build/desktop && cmake ../..

configure-web:
	@mkdir -p build/web
	@cd build/web && emcmake cmake ../..

run-web:
	@cd build/web && python3 -m http.server

run-desktop:
	@cd build/desktop && ./TiKiRa

clean:
	@rm -rf build/desktop
	@rm -rf build/web
