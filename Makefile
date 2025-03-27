.PHONY: release

PKGCONFIG = pkg-config
LUA = lua
CFLAGS = -g -fPIC $(shell $(PKGCONFIG) --cflags $(LUA))
LDFLAGS = -shared

VERSION = $(shell LUA_CPATH="./csrc/?.so" lua -e 'print(table.pack(require("TagLib._VERSION"))[1])')

release: csrc/TagLib.so
	rm -rf dist/lua-taglib-$(VERSION)
	rm -rf dist/lua-taglib-$(VERSION).tar.gz
	rm -rf dist/lua-taglib-$(VERSION).tar.xz
	mkdir -p dist/lua-taglib-$(VERSION)/csrc
	rsync -a --exclude='*.so' csrc/ dist/lua-taglib-$(VERSION)/csrc/
	rsync -a cmake/ dist/lua-taglib-$(VERSION)/cmake/
	rsync -a LICENSE dist/lua-taglib-$(VERSION)/LICENSE
	rsync -a README.md dist/lua-taglib-$(VERSION)/README.md
	rsync -a CMakeLists.txt dist/lua-taglib-$(VERSION)/CMakeLists.txt
	sed 's/@VERSION@/$(VERSION)/g' < rockspec/taglib-template.rockspec > dist/lua-taglib-$(VERSION)/taglib-$(VERSION)-1.rockspec
	cd dist && tar --owner=0 --group=0 -c -f lua-taglib-$(VERSION).tar lua-taglib-$(VERSION)
	cd dist && gzip -k lua-taglib-$(VERSION).tar
	cd dist && xz lua-taglib-$(VERSION).tar

csrc/TagLib.so: csrc/version.c csrc/version.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


clean:
	rm -f csrc/TagLib.so
