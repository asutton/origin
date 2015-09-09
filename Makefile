
tgt = index.html \
		  start.html \
		  ref/concepts.html \
		  ref/concepts/language.html \
		  ref/concepts/integral_type.html \
		  ref/concepts/value.html \
		  ref/concepts/destructible.html \
		  ref/concepts/constructible.html \
		  ref/concepts/equality.html \
		  ref/concepts/regular.html \
		  ref/concepts/semiregular.html \
		  ref/concepts/function.html \

PANDOC_INC = -H include/prelude.html -B include/header.html -A include/footer.html
PANDOC_FLAGS = -s -S ${PANDOC_INC}

%.html: %.md include/prelude.html include/header.html include/footer.html
	pandoc ${PANDOC_FLAGS} $< -o $@


all: ${tgt}

clean:
	rm -f ${tgt}

