
p = print

from params import *

if __name__ == '__main__':
    p(".data")
    p(".section .rodata")
    p(".align 32")

    p(".text")
    p(".hidden PQCLEAN_NTRUHPS2048509_AVX2_poly_mod_q_Phi_n")
    p(".global PQCLEAN_NTRUHPS2048509_AVX2_poly_mod_q_Phi_n")
    p(".att_syntax prefix")

    p("PQCLEAN_NTRUHPS2048509_AVX2_poly_mod_q_Phi_n:")
    # rdi holds r

    N_min_1 = 0
    t = 1
    # NTRU_N is in 509th element; 13th word of 32nd register
    p("vmovdqa {}(%rdi), %ymm{}".format(31*32, N_min_1))
    p("vpermq ${}, %ymm{}, %ymm{}".format(int('00000011', 2), N_min_1, N_min_1))
    # move into high 16 in doubleword (to clear high 16)
    p("vpslld $16, %ymm{}, %ymm{}".format(N_min_1, N_min_1))
    # clone into bottom 16
    p("vpsrld $16, %ymm{}, %ymm{}".format(N_min_1, t))
    p("vpor %ymm{}, %ymm{}, %ymm{}".format(N_min_1, t, N_min_1))
    # and now it's everywhere in N_min_1
    p("vbroadcastss %xmm{}, %ymm{}".format(N_min_1, N_min_1))
    # negate it
    p("vxorpd %ymm{}, %ymm{}, %ymm{}".format(t,t,t))
    p("vpsubw %ymm{}, %ymm{}, %ymm{}".format(N_min_1, t, N_min_1))

    for i in range(NTRU_N32//16):
        p("vpaddw {}(%rdi), %ymm{}, %ymm{}".format(i*32, N_min_1, t))
        p("vmovdqa %ymm{}, {}(%rdi)".format(t, i*32))

    p("ret")
