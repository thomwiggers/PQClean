LIB=libntruhps2048509_avx2.a
CFLAGS=-O3 -mavx2 -mbmi2 -Wall -Wextra -Wpedantic -Wvla -Werror -Wredundant-decls -std=gnu99 -I../../../common $(EXTRAFLAGS)

SRC = crypto_sort_int32.c \
      djbsort/sort.c \
      kem.c \
      owcpa.c \
      pack3.c \
      packq.c \
      poly.c \
      poly_lift.c \
      poly_r2_inv.c \
      poly_s3_inv.c \
      sample.c \
      sample_iid.c \
      verify.c


HEADERS = djbsort/int32_sort.h\
      crypto_sort_int32.h \
      kem.h \
      owcpa.h \
      params.h \
      poly.h \
      poly_r2_inv.h \
      sample.h \
      verify.h


SOBJS = square_1_509_patience.s \
       square_3_509_patience.s \
       square_6_509_patience.s \
       square_15_509_shufbytes.s \
       square_30_509_shufbytes.s \
       square_63_509_shufbytes.s \
       square_126_509_shufbytes.s \
       square_252_509_shufbytes.s

SOBJS += poly_rq_mul.s \
        poly_r2_mul.s \
        poly_rq_to_s3.s \
        vec32_sample_iid.s \
        poly_mod_3_Phi_n.s \
        poly_mod_q_Phi_n.s

OBJECTS = $(subst .c,.o,${SRC}) $(subst .s,.o,${SOBJS})

all: $(LIB)

poly_s3_inv.c: asmgen/poly_s3_inv.py
	python3 $^ 508 | sed 's/4294967295/-1/g' > $@

poly_rq_mul.s: asmgen/rq_mul/poly_rq_mul.py asmgen/rq_mul/K2_schoolbook_64x8.py asmgen/rq_mul/K2_K2_64x32.py
	python3 $^ > $@

%.s: asmgen/%.py
	python3 $^ > $@

square_%_shufbytes.s: $(wildcard bitpermutations/*)
	PYTHONPATH=bitpermutations \
	 python3 bitpermutations/applications/squaring_mod_GF2N.py \
	 --shufbytes --raw-name $(word 2, $(subst _, ,$@)) \
	 > $@

square_%_patience.s: $(wildcard bitpermutations/*)
	PYTHONPATH=bitpermutations \
	 python3 bitpermutations/applications/squaring_mod_GF2N.py \
	 --patience --callee 6 --raw-name $(word 2, $(subst _, ,$@)) \
	 > $@

.PHONY: clean

clean:
	-find . -name '*.pyc' -delete
	-find . -name '__pycache__' -delete
	-$(RM) *.o
	-$(RM) poly_s3_inv.c
	-$(RM) -r test/test_polymul
	-$(RM) -r test/test_ntru
	-$(RM) -r test/test_pack
	-$(RM) -r test/speed
	-$(RM) -r test/ram
	-$(RM) -r test/encap
	-$(RM) -r test/decap
	-$(RM) -r test/keypair
	-$(RM) -r test/speed_r2_inv
	-$(RM) PQCgenKAT_kem
	-$(RM) PQCkemKAT_*.req
	-$(RM) PQCkemKAT_*.rsp
	-$(RM) $(LIB)



$(LIB): $(OBJECTS) $(HEADERS)
	$(AR) -r $@ $^

