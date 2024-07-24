.PHONY: all clean desktop web run-web

all: desktop

desktop:
	@if [ ! -f "build/desktop/CMakeCache.txt" ]; then $(MAKE) configure-desktop; fi
	@cd build/desktop && cmake --build .

web:
	@if [ ! -d "build/web" ]; then $(MAKE) configure-web; fi
	@cd build/web && emmake make

test:
	@if [ ! -d "build/tests" ]; then $(MAKE) configure-tests; fi
	@cd build/tests && cmake --build . && ctest --verbose --output-on-failure

configure-with-address-sanitizer:
	@mkdir -p build/desktop
	@cd build/desktop && cmake -DUSE_ASAN=ON ../..

configure-with-memory-sanitizer:
	@mkdir -p build/desktop
	@cd build/desktop && cmake -DUSE_MSAN=ON ../..

configure-desktop:
	@mkdir -p build/desktop
	@cd build/desktop && cmake ../..

configure-tests:
	@mkdir -p build/tests
	@cd build/tests && cmake -DBUILD_TESTS=ON ../..

configure-web:
	@mkdir -p build/web
	@cd build/web && emcmake cmake -DEMSCRIPTEN=ON ../..

run-web:
	@cd build/web && python3 -m http.server

run-desktop:
	@cd build/desktop && ./TiKiRa

clean:
	@for item in build/*; do \
		if [ "$$item" != "build/desktop" ]; then \
			rm -rf "$$item"; \
		else \
			for subitem in build/desktop/*; do \
				if [ "$$subitem" != "build/desktop/external" ]; then \
					rm -rf "$$subitem"; \
				fi \
			done \
		fi \
	done
