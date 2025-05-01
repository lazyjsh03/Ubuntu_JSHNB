SUBDIRS := ch01 ch02 ch03 ch04 ch05 ch06 ch07 ch08 ch09 ch10

all : compile

compile:
	@for DIR in $(SUBDIRS); do \
		make -C $$DIR || exit $?; \
	done

clean:
	@for DIR in $(SUBDIRS); do \
		make -C $$DIR clean; \
	done
