SUBROUTINE bl_init()
    call random_seed()
END

SUBROUTINE bl_dcross(A, B, C)
    use iso_c_binding
    real(c_double) :: A(3), B(3), C(3)
    C(1) = A(2) * B(3) - A(3) * B(2)
    C(2) = A(3) * B(1) - A(1) * B(3)
    C(3) = A(1) * B(2) - A(2) * B(1)
END

SUBROUTINE bl_scross(A, B, C)
    use iso_c_binding
    real(c_float) :: A(3), B(3), C(3)
    C(1) = A(2) * B(3) - A(3) * B(2)
    C(2) = A(3) * B(1) - A(1) * B(3)
    C(3) = A(1) * B(2) - A(2) * B(1)
END

SUBROUTINE bl_dtranspose(A, M, N, B)
    use iso_c_binding,
    INTEGER(c_int) :: M, N
    real(c_double) :: A(M,N)
    real(c_double) :: B(N,M)
    B = transpose(A)
END

SUBROUTINE bl_stranspose(A, M, N, B)
    use iso_c_binding,
    INTEGER(c_int) :: M, N
    real(c_float) :: A(M,N)
    real(c_float) :: B(N,M)
    B = transpose(A)
END

SUBROUTINE bl_drand(A)
    use iso_c_binding,
    real(c_double) :: A
    call RANDOM_NUMBER(A)
END

SUBROUTINE bl_drandom(A, M, N)
    use iso_c_binding,
    INTEGER(c_int) :: M, N
    real(c_double) :: A(M, N)
    call RANDOM_NUMBER(A)
END

SUBROUTINE bl_random(A, M, N)
    use iso_c_binding,
    INTEGER(c_int) :: M, N
    real(c_float) :: A(M, N)
    call RANDOM_NUMBER(A)
END