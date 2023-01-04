; _______________________________________________________________________
; P REISS   03/04
; CATPierreAsm.h = fichier include commun a tous les .asm pour ml64.exe
; cf //webster.cs.ucr.edu/AsmTools/MASM/MASMDoc/ProgrammersGuide
; utilisation:
;   INCLUDE CATPierreAsm.h
;   ml64 /I.                         (command line)
; xmmA remplace par le symbole xmm10
; ymmA remplace par le symbole ymm10 (architecture AVX)
; ammN evite de reconnaitre un argument de macro comme un mot-cle
; _______________________________________________________________________

xmmA TEXTEQU <xmm10>
xmmB TEXTEQU <xmm11>
xmmC TEXTEQU <xmm12>
xmmD TEXTEQU <xmm13>
xmmE TEXTEQU <xmm14>
xmmF TEXTEQU <xmm15>

ymmA TEXTEQU <ymm10>
ymmB TEXTEQU <ymm11>
ymmC TEXTEQU <ymm12>
ymmD TEXTEQU <ymm13>
ymmE TEXTEQU <ymm14>
ymmF TEXTEQU <ymm15>

amm0 TEXTEQU <bmm0>
amm1 TEXTEQU <bmm1>
amm2 TEXTEQU <bmm2>
amm3 TEXTEQU <bmm3>
amm4 TEXTEQU <bmm4>
amm5 TEXTEQU <bmm5>
amm6 TEXTEQU <bmm6>
amm7 TEXTEQU <bmm7>
amm8 TEXTEQU <bmm8>
amm9 TEXTEQU <bmm9>
ammA TEXTEQU <bmmA>
ammB TEXTEQU <bmmB>
ammC TEXTEQU <bmmC>
ammD TEXTEQU <bmmD>
ammE TEXTEQU <bmmE>
ammF TEXTEQU <bmmF>

HWORD TEXTEQU <YMMWORD>
; _______________________________________________________________________
