include Config.mk

srend: ${srend_obj}
	${CC} $^ ${cflags} -o $@
out/%.o: src/%.c ${srend_inc}
	${CC} $< ${cflags} ${srend_preclude} -c -o $@

clean:
	rm out/*.o
	rm srend

.PHONY: clean