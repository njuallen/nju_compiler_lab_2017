.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

main:
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -400
  addi $sp, $sp, -4
  sw $t0, -404($fp)
  li $t0, 100
  addi $sp, $sp, -4
  sw $t1, -408($fp)
  addi $t1, $fp, -400
  addi $sp, $sp, -4
  sw $t2, -412($fp)
  li $t2, 0
  addi $sp, $sp, -4
  sw $t3, -416($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -420($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t5, -424($fp)
  add $t5, $t1, $t4
  addi $sp, $sp, -4
  sw $t6, -428($fp)
  li $t6, 81
  sw $t6, 0($t5)
  addi $sp, $sp, -4
  sw $t7, -432($fp)
  lw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -436($fp)
  li $t8, 1
  addi $sp, $sp, -4
  sw $t9, -440($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -444($fp)
  mul $s0, $t8, $t9
  addi $sp, $sp, -4
  sw $s1, -448($fp)
  add $s1, $t1, $s0
  addi $sp, $sp, -4
  sw $s2, -452($fp)
  li $s2, 37
  sw $s2, 0($s1)
  addi $sp, $sp, -4
  sw $s3, -456($fp)
  lw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $s4, -460($fp)
  li $s4, 2
  addi $sp, $sp, -4
  sw $s5, -464($fp)
  li $s5, 4
  addi $sp, $sp, -4
  sw $s6, -468($fp)
  mul $s6, $s4, $s5
  addi $sp, $sp, -4
  sw $s7, -472($fp)
  add $s7, $t1, $s6
  addi $sp, $sp, -4
  sw $t0, -476($fp)
  li $t0, 64
  sw $t0, 0($s7)
  addi $sp, $sp, -4
  sw $t1, -480($fp)
  lw $t1, 0($s7)
  addi $sp, $sp, -4
  sw $t2, -484($fp)
  li $t2, 3
  addi $sp, $sp, -4
  sw $t3, -488($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -492($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t5, -496($fp)
  addi $sp, $sp, -4
  sw $t6, -500($fp)
  lw $t6, -480($fp)
  add $t5, $t6, $t4
  addi $sp, $sp, -4
  sw $t7, -504($fp)
  li $t7, 23
  sw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -508($fp)
  lw $t8, 0($t5)
  addi $sp, $sp, -4
  sw $t9, -512($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -516($fp)
  li $s0, 4
  addi $sp, $sp, -4
  sw $s1, -520($fp)
  mul $s1, $t9, $s0
  addi $sp, $sp, -4
  sw $s2, -524($fp)
  add $s2, $t6, $s1
  addi $sp, $sp, -4
  sw $s3, -528($fp)
  li $s3, 38
  sw $s3, 0($s2)
  addi $sp, $sp, -4
  sw $s4, -532($fp)
  lw $s4, 0($s2)
  addi $sp, $sp, -4
  sw $s5, -536($fp)
  li $s5, 5
  addi $sp, $sp, -4
  sw $s6, -540($fp)
  li $s6, 4
  addi $sp, $sp, -4
  sw $s7, -544($fp)
  mul $s7, $s5, $s6
  addi $sp, $sp, -4
  sw $t0, -548($fp)
  add $t0, $t6, $s7
  addi $sp, $sp, -4
  sw $t1, -552($fp)
  li $t1, 65
  sw $t1, 0($t0)
  addi $sp, $sp, -4
  sw $t2, -556($fp)
  lw $t2, 0($t0)
  addi $sp, $sp, -4
  sw $t3, -560($fp)
  li $t3, 6
  addi $sp, $sp, -4
  sw $t4, -564($fp)
  li $t4, 4
  addi $sp, $sp, -4
  sw $t5, -568($fp)
  mul $t5, $t3, $t4
  addi $sp, $sp, -4
  sw $t7, -572($fp)
  lw $t7, -480($fp)
  add $t6, $t7, $t5
  addi $sp, $sp, -4
  sw $t8, -576($fp)
  li $t8, 56
  sw $t8, 0($t6)
  addi $sp, $sp, -4
  sw $t9, -580($fp)
  lw $t9, 0($t6)
  addi $sp, $sp, -4
  sw $s0, -584($fp)
  li $s0, 7
  addi $sp, $sp, -4
  sw $s1, -588($fp)
  li $s1, 4
  addi $sp, $sp, -4
  sw $s2, -592($fp)
  mul $s2, $s0, $s1
  addi $sp, $sp, -4
  sw $s3, -596($fp)
  add $s3, $t7, $s2
  addi $sp, $sp, -4
  sw $s4, -600($fp)
  li $s4, 15
  sw $s4, 0($s3)
  addi $sp, $sp, -4
  sw $s5, -604($fp)
  lw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $s6, -608($fp)
  li $s6, 8
  addi $sp, $sp, -4
  sw $s7, -612($fp)
  li $s7, 4
  addi $sp, $sp, -4
  sw $t0, -616($fp)
  mul $t0, $s6, $s7
  addi $sp, $sp, -4
  sw $t1, -620($fp)
  add $t1, $t7, $t0
  addi $sp, $sp, -4
  sw $t2, -624($fp)
  li $t2, 8
  sw $t2, 0($t1)
  addi $sp, $sp, -4
  sw $t3, -628($fp)
  lw $t3, 0($t1)
  addi $sp, $sp, -4
  sw $t4, -632($fp)
  li $t4, 9
  addi $sp, $sp, -4
  sw $t5, -636($fp)
  li $t5, 4
  addi $sp, $sp, -4
  sw $t6, -640($fp)
  mul $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $t8, -644($fp)
  lw $t8, -480($fp)
  add $t7, $t8, $t6
  addi $sp, $sp, -4
  sw $t9, -648($fp)
  li $t9, 33
  sw $t9, 0($t7)
  addi $sp, $sp, -4
  sw $s0, -652($fp)
  lw $s0, 0($t7)
  addi $sp, $sp, -4
  sw $s1, -656($fp)
  li $s1, 10
  addi $sp, $sp, -4
  sw $s2, -660($fp)
  li $s2, 4
  addi $sp, $sp, -4
  sw $s3, -664($fp)
  mul $s3, $s1, $s2
  addi $sp, $sp, -4
  sw $s4, -668($fp)
  add $s4, $t8, $s3
  addi $sp, $sp, -4
  sw $s5, -672($fp)
  li $s5, 85
  sw $s5, 0($s4)
  addi $sp, $sp, -4
  sw $s6, -676($fp)
  lw $s6, 0($s4)
  addi $sp, $sp, -4
  sw $s7, -680($fp)
  li $s7, 11
  addi $sp, $sp, -4
  sw $t0, -684($fp)
  li $t0, 4
  addi $sp, $sp, -4
  sw $t1, -688($fp)
  mul $t1, $s7, $t0
  addi $sp, $sp, -4
  sw $t2, -692($fp)
  add $t2, $t8, $t1
  addi $sp, $sp, -4
  sw $t3, -696($fp)
  li $t3, 39
  sw $t3, 0($t2)
  addi $sp, $sp, -4
  sw $t4, -700($fp)
  lw $t4, 0($t2)
  addi $sp, $sp, -4
  sw $t5, -704($fp)
  li $t5, 12
  addi $sp, $sp, -4
  sw $t6, -708($fp)
  li $t6, 4
  addi $sp, $sp, -4
  sw $t7, -712($fp)
  mul $t7, $t5, $t6
  addi $sp, $sp, -4
  sw $t9, -716($fp)
  lw $t9, -480($fp)
  add $t8, $t9, $t7
  addi $sp, $sp, -4
  sw $s0, -720($fp)
  li $s0, 71
  sw $s0, 0($t8)
  addi $sp, $sp, -4
  sw $s1, -724($fp)
  lw $s1, 0($t8)
  addi $sp, $sp, -4
  sw $s2, -728($fp)
  li $s2, 13
  addi $sp, $sp, -4
  sw $s3, -732($fp)
  li $s3, 4
  addi $sp, $sp, -4
  sw $s4, -736($fp)
  mul $s4, $s2, $s3
  addi $sp, $sp, -4
  sw $s5, -740($fp)
  add $s5, $t9, $s4
  addi $sp, $sp, -4
  sw $s6, -744($fp)
  li $s6, 12
  sw $s6, 0($s5)
  addi $sp, $sp, -4
  sw $s7, -748($fp)
  lw $s7, 0($s5)
  addi $sp, $sp, -4
  sw $t0, -752($fp)
  li $t0, 14
  addi $sp, $sp, -4
  sw $t1, -756($fp)
  li $t1, 4
  addi $sp, $sp, -4
  sw $t2, -760($fp)
  mul $t2, $t0, $t1
  addi $sp, $sp, -4
  sw $t3, -764($fp)
  add $t3, $t9, $t2
  addi $sp, $sp, -4
  sw $t4, -768($fp)
  li $t4, 77
  sw $t4, 0($t3)
  addi $sp, $sp, -4
  sw $t5, -772($fp)
  lw $t5, 0($t3)
  addi $sp, $sp, -4
  sw $t6, -776($fp)
  li $t6, 15
  addi $sp, $sp, -4
  sw $t7, -780($fp)
  li $t7, 4
  addi $sp, $sp, -4
  sw $t8, -784($fp)
  mul $t8, $t6, $t7
  addi $sp, $sp, -4
  sw $s0, -788($fp)
  lw $s0, -480($fp)
  add $t9, $s0, $t8
  addi $sp, $sp, -4
  sw $s1, -792($fp)
  li $s1, 6
  sw $s1, 0($t9)
  addi $sp, $sp, -4
  sw $s2, -796($fp)
  lw $s2, 0($t9)
  addi $sp, $sp, -4
  sw $s3, -800($fp)
  li $s3, 16
  addi $sp, $sp, -4
  sw $s4, -804($fp)
  li $s4, 4
  addi $sp, $sp, -4
  sw $s5, -808($fp)
  mul $s5, $s3, $s4
  addi $sp, $sp, -4
  sw $s6, -812($fp)
  add $s6, $s0, $s5
  addi $sp, $sp, -4
  sw $s7, -816($fp)
  li $s7, 82
  sw $s7, 0($s6)
  addi $sp, $sp, -4
  sw $t0, -820($fp)
  lw $t0, 0($s6)
  addi $sp, $sp, -4
  sw $t1, -824($fp)
  li $t1, 17
  addi $sp, $sp, -4
  sw $t2, -828($fp)
  li $t2, 4
  addi $sp, $sp, -4
  sw $t3, -832($fp)
  mul $t3, $t1, $t2
  addi $sp, $sp, -4
  sw $t4, -836($fp)
  add $t4, $s0, $t3
  addi $sp, $sp, -4
  sw $t5, -840($fp)
  li $t5, 89
  sw $t5, 0($t4)
  addi $sp, $sp, -4
  sw $t6, -844($fp)
  lw $t6, 0($t4)
  addi $sp, $sp, -4
  sw $t7, -848($fp)
  li $t7, 18
  addi $sp, $sp, -4
  sw $t8, -852($fp)
  li $t8, 4
  addi $sp, $sp, -4
  sw $t9, -856($fp)
  mul $t9, $t7, $t8
  addi $sp, $sp, -4
  sw $s1, -860($fp)
  lw $s1, -480($fp)
  add $s0, $s1, $t9
  addi $sp, $sp, -4
  sw $s2, -864($fp)
  li $s2, 80
  sw $s2, 0($s0)
  addi $sp, $sp, -4
  sw $s3, -868($fp)
  lw $s3, 0($s0)
  addi $sp, $sp, -4
  sw $s4, -872($fp)
  li $s4, 19
  addi $sp, $sp, -4
  sw $s5, -876($fp)
  li $s5, 4
  addi $sp, $sp, -4
  sw $s6, -880($fp)
  mul $s6, $s4, $s5
  addi $sp, $sp, -4
  sw $s7, -884($fp)
  add $s7, $s1, $s6
  addi $sp, $sp, -4
  sw $t0, -888($fp)
  li $t0, 35
  sw $t0, 0($s7)
  addi $sp, $sp, -4
  sw $t1, -892($fp)
  lw $t1, 0($s7)
  addi $sp, $sp, -4
  sw $t2, -896($fp)
  li $t2, 20
  addi $sp, $sp, -4
  sw $t3, -900($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -904($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t5, -908($fp)
  add $t5, $s1, $t4
  addi $sp, $sp, -4
  sw $t6, -912($fp)
  li $t6, 0
  sw $t6, 0($t5)
  addi $sp, $sp, -4
  sw $t7, -916($fp)
  lw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -920($fp)
  li $t8, 21
  addi $sp, $sp, -4
  sw $t9, -924($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -928($fp)
  mul $s0, $t8, $t9
  addi $sp, $sp, -4
  sw $s2, -932($fp)
  lw $s2, -480($fp)
  add $s1, $s2, $s0
  addi $sp, $sp, -4
  sw $s3, -936($fp)
  li $s3, 59
  sw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $s4, -940($fp)
  lw $s4, 0($s1)
  addi $sp, $sp, -4
  sw $s5, -944($fp)
  li $s5, 22
  addi $sp, $sp, -4
  sw $s6, -948($fp)
  li $s6, 4
  addi $sp, $sp, -4
  sw $s7, -952($fp)
  mul $s7, $s5, $s6
  addi $sp, $sp, -4
  sw $t0, -956($fp)
  add $t0, $s2, $s7
  addi $sp, $sp, -4
  sw $t1, -960($fp)
  li $t1, 73
  sw $t1, 0($t0)
  addi $sp, $sp, -4
  sw $t2, -964($fp)
  lw $t2, 0($t0)
  addi $sp, $sp, -4
  sw $t3, -968($fp)
  li $t3, 23
  addi $sp, $sp, -4
  sw $t4, -972($fp)
  li $t4, 4
  addi $sp, $sp, -4
  sw $t5, -976($fp)
  mul $t5, $t3, $t4
  addi $sp, $sp, -4
  sw $t6, -980($fp)
  add $t6, $s2, $t5
  addi $sp, $sp, -4
  sw $t7, -984($fp)
  li $t7, 4
  sw $t7, 0($t6)
  addi $sp, $sp, -4
  sw $t8, -988($fp)
  lw $t8, 0($t6)
  addi $sp, $sp, -4
  sw $t9, -992($fp)
  li $t9, 24
  addi $sp, $sp, -4
  sw $s0, -996($fp)
  li $s0, 4
  addi $sp, $sp, -4
  sw $s1, -1000($fp)
  mul $s1, $t9, $s0
  addi $sp, $sp, -4
  sw $s3, -1004($fp)
  lw $s3, -480($fp)
  add $s2, $s3, $s1
  addi $sp, $sp, -4
  sw $s4, -1008($fp)
  li $s4, 61
  sw $s4, 0($s2)
  addi $sp, $sp, -4
  sw $s5, -1012($fp)
  lw $s5, 0($s2)
  addi $sp, $sp, -4
  sw $s6, -1016($fp)
  li $s6, 25
  addi $sp, $sp, -4
  sw $s7, -1020($fp)
  li $s7, 4
  addi $sp, $sp, -4
  sw $t0, -1024($fp)
  mul $t0, $s6, $s7
  addi $sp, $sp, -4
  sw $t1, -1028($fp)
  add $t1, $s3, $t0
  addi $sp, $sp, -4
  sw $t2, -1032($fp)
  li $t2, 30
  sw $t2, 0($t1)
  addi $sp, $sp, -4
  sw $t3, -1036($fp)
  lw $t3, 0($t1)
  addi $sp, $sp, -4
  sw $t4, -1040($fp)
  li $t4, 26
  addi $sp, $sp, -4
  sw $t5, -1044($fp)
  li $t5, 4
  addi $sp, $sp, -4
  sw $t6, -1048($fp)
  mul $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $t7, -1052($fp)
  add $t7, $s3, $t6
  addi $sp, $sp, -4
  sw $t8, -1056($fp)
  li $t8, 74
  sw $t8, 0($t7)
  addi $sp, $sp, -4
  sw $t9, -1060($fp)
  lw $t9, 0($t7)
  addi $sp, $sp, -4
  sw $s0, -1064($fp)
  li $s0, 27
  addi $sp, $sp, -4
  sw $s1, -1068($fp)
  li $s1, 4
  addi $sp, $sp, -4
  sw $s2, -1072($fp)
  mul $s2, $s0, $s1
  addi $sp, $sp, -4
  sw $s4, -1076($fp)
  lw $s4, -480($fp)
  add $s3, $s4, $s2
  addi $sp, $sp, -4
  sw $s5, -1080($fp)
  li $s5, 69
  sw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $s6, -1084($fp)
  lw $s6, 0($s3)
  addi $sp, $sp, -4
  sw $s7, -1088($fp)
  li $s7, 28
  addi $sp, $sp, -4
  sw $t0, -1092($fp)
  li $t0, 4
  addi $sp, $sp, -4
  sw $t1, -1096($fp)
  mul $t1, $s7, $t0
  addi $sp, $sp, -4
  sw $t2, -1100($fp)
  add $t2, $s4, $t1
  addi $sp, $sp, -4
  sw $t3, -1104($fp)
  li $t3, 13
  sw $t3, 0($t2)
  addi $sp, $sp, -4
  sw $t4, -1108($fp)
  lw $t4, 0($t2)
  addi $sp, $sp, -4
  sw $t5, -1112($fp)
  li $t5, 29
  addi $sp, $sp, -4
  sw $t6, -1116($fp)
  li $t6, 4
  addi $sp, $sp, -4
  sw $t7, -1120($fp)
  mul $t7, $t5, $t6
  addi $sp, $sp, -4
  sw $t8, -1124($fp)
  add $t8, $s4, $t7
  addi $sp, $sp, -4
  sw $t9, -1128($fp)
  li $t9, 42
  sw $t9, 0($t8)
  addi $sp, $sp, -4
  sw $s0, -1132($fp)
  lw $s0, 0($t8)
  addi $sp, $sp, -4
  sw $s1, -1136($fp)
  li $s1, 30
  addi $sp, $sp, -4
  sw $s2, -1140($fp)
  li $s2, 4
  addi $sp, $sp, -4
  sw $s3, -1144($fp)
  mul $s3, $s1, $s2
  addi $sp, $sp, -4
  sw $s5, -1148($fp)
  lw $s5, -480($fp)
  add $s4, $s5, $s3
  addi $sp, $sp, -4
  sw $s6, -1152($fp)
  li $s6, 68
  sw $s6, 0($s4)
  addi $sp, $sp, -4
  sw $s7, -1156($fp)
  lw $s7, 0($s4)
  addi $sp, $sp, -4
  sw $t0, -1160($fp)
  li $t0, 31
  addi $sp, $sp, -4
  sw $t1, -1164($fp)
  li $t1, 4
  addi $sp, $sp, -4
  sw $t2, -1168($fp)
  mul $t2, $t0, $t1
  addi $sp, $sp, -4
  sw $t3, -1172($fp)
  add $t3, $s5, $t2
  addi $sp, $sp, -4
  sw $t4, -1176($fp)
  li $t4, 63
  sw $t4, 0($t3)
  addi $sp, $sp, -4
  sw $t5, -1180($fp)
  lw $t5, 0($t3)
  addi $sp, $sp, -4
  sw $t6, -1184($fp)
  li $t6, 32
  addi $sp, $sp, -4
  sw $t7, -1188($fp)
  li $t7, 4
  addi $sp, $sp, -4
  sw $t8, -1192($fp)
  mul $t8, $t6, $t7
  addi $sp, $sp, -4
  sw $t9, -1196($fp)
  add $t9, $s5, $t8
  addi $sp, $sp, -4
  sw $s0, -1200($fp)
  li $s0, 9
  sw $s0, 0($t9)
  addi $sp, $sp, -4
  sw $s1, -1204($fp)
  lw $s1, 0($t9)
  addi $sp, $sp, -4
  sw $s2, -1208($fp)
  li $s2, 33
  addi $sp, $sp, -4
  sw $s3, -1212($fp)
  li $s3, 4
  addi $sp, $sp, -4
  sw $s4, -1216($fp)
  mul $s4, $s2, $s3
  addi $sp, $sp, -4
  sw $s6, -1220($fp)
  lw $s6, -480($fp)
  add $s5, $s6, $s4
  addi $sp, $sp, -4
  sw $s7, -1224($fp)
  li $s7, 29
  sw $s7, 0($s5)
  addi $sp, $sp, -4
  sw $t0, -1228($fp)
  lw $t0, 0($s5)
  addi $sp, $sp, -4
  sw $t1, -1232($fp)
  li $t1, 34
  addi $sp, $sp, -4
  sw $t2, -1236($fp)
  li $t2, 4
  addi $sp, $sp, -4
  sw $t3, -1240($fp)
  mul $t3, $t1, $t2
  addi $sp, $sp, -4
  sw $t4, -1244($fp)
  add $t4, $s6, $t3
  addi $sp, $sp, -4
  sw $t5, -1248($fp)
  li $t5, 47
  sw $t5, 0($t4)
  addi $sp, $sp, -4
  sw $t6, -1252($fp)
  lw $t6, 0($t4)
  addi $sp, $sp, -4
  sw $t7, -1256($fp)
  li $t7, 35
  addi $sp, $sp, -4
  sw $t8, -1260($fp)
  li $t8, 4
  addi $sp, $sp, -4
  sw $t9, -1264($fp)
  mul $t9, $t7, $t8
  addi $sp, $sp, -4
  sw $s0, -1268($fp)
  add $s0, $s6, $t9
  addi $sp, $sp, -4
  sw $s1, -1272($fp)
  li $s1, 36
  sw $s1, 0($s0)
  addi $sp, $sp, -4
  sw $s2, -1276($fp)
  lw $s2, 0($s0)
  addi $sp, $sp, -4
  sw $s3, -1280($fp)
  li $s3, 36
  addi $sp, $sp, -4
  sw $s4, -1284($fp)
  li $s4, 4
  addi $sp, $sp, -4
  sw $s5, -1288($fp)
  mul $s5, $s3, $s4
  addi $sp, $sp, -4
  sw $s7, -1292($fp)
  lw $s7, -480($fp)
  add $s6, $s7, $s5
  addi $sp, $sp, -4
  sw $t0, -1296($fp)
  li $t0, 99
  sw $t0, 0($s6)
  addi $sp, $sp, -4
  sw $t1, -1300($fp)
  lw $t1, 0($s6)
  addi $sp, $sp, -4
  sw $t2, -1304($fp)
  li $t2, 37
  addi $sp, $sp, -4
  sw $t3, -1308($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -1312($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t5, -1316($fp)
  add $t5, $s7, $t4
  addi $sp, $sp, -4
  sw $t6, -1320($fp)
  li $t6, 25
  sw $t6, 0($t5)
  addi $sp, $sp, -4
  sw $t7, -1324($fp)
  lw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -1328($fp)
  li $t8, 38
  addi $sp, $sp, -4
  sw $t9, -1332($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -1336($fp)
  mul $s0, $t8, $t9
  addi $sp, $sp, -4
  sw $s1, -1340($fp)
  add $s1, $s7, $s0
  addi $sp, $sp, -4
  sw $s2, -1344($fp)
  li $s2, 21
  sw $s2, 0($s1)
  addi $sp, $sp, -4
  sw $s3, -1348($fp)
  lw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $s4, -1352($fp)
  li $s4, 39
  addi $sp, $sp, -4
  sw $s5, -1356($fp)
  li $s5, 4
  addi $sp, $sp, -4
  sw $s6, -1360($fp)
  mul $s6, $s4, $s5
  addi $sp, $sp, -4
  sw $t0, -1364($fp)
  lw $t0, -480($fp)
  add $s7, $t0, $s6
  addi $sp, $sp, -4
  sw $t1, -1368($fp)
  li $t1, 14
  sw $t1, 0($s7)
  addi $sp, $sp, -4
  sw $t2, -1372($fp)
  lw $t2, 0($s7)
  addi $sp, $sp, -4
  sw $t3, -1376($fp)
  li $t3, 40
  addi $sp, $sp, -4
  sw $t4, -1380($fp)
  li $t4, 4
  addi $sp, $sp, -4
  sw $t5, -1384($fp)
  mul $t5, $t3, $t4
  addi $sp, $sp, -4
  sw $t6, -1388($fp)
  add $t6, $t0, $t5
  addi $sp, $sp, -4
  sw $t7, -1392($fp)
  li $t7, 60
  sw $t7, 0($t6)
  addi $sp, $sp, -4
  sw $t8, -1396($fp)
  lw $t8, 0($t6)
  addi $sp, $sp, -4
  sw $t9, -1400($fp)
  li $t9, 41
  addi $sp, $sp, -4
  sw $s0, -1404($fp)
  li $s0, 4
  addi $sp, $sp, -4
  sw $s1, -1408($fp)
  mul $s1, $t9, $s0
  addi $sp, $sp, -4
  sw $s2, -1412($fp)
  add $s2, $t0, $s1
  addi $sp, $sp, -4
  sw $s3, -1416($fp)
  li $s3, 3
  sw $s3, 0($s2)
  addi $sp, $sp, -4
  sw $s4, -1420($fp)
  lw $s4, 0($s2)
  addi $sp, $sp, -4
  sw $s5, -1424($fp)
  li $s5, 42
  addi $sp, $sp, -4
  sw $s6, -1428($fp)
  li $s6, 4
  addi $sp, $sp, -4
  sw $s7, -1432($fp)
  mul $s7, $s5, $s6
  addi $sp, $sp, -4
  sw $t1, -1436($fp)
  lw $t1, -480($fp)
  add $t0, $t1, $s7
  addi $sp, $sp, -4
  sw $t2, -1440($fp)
  li $t2, 2
  sw $t2, 0($t0)
  addi $sp, $sp, -4
  sw $t3, -1444($fp)
  lw $t3, 0($t0)
  addi $sp, $sp, -4
  sw $t4, -1448($fp)
  li $t4, 43
  addi $sp, $sp, -4
  sw $t5, -1452($fp)
  li $t5, 4
  addi $sp, $sp, -4
  sw $t6, -1456($fp)
  mul $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $t7, -1460($fp)
  add $t7, $t1, $t6
  addi $sp, $sp, -4
  sw $t8, -1464($fp)
  li $t8, 18
  sw $t8, 0($t7)
  addi $sp, $sp, -4
  sw $t9, -1468($fp)
  lw $t9, 0($t7)
  addi $sp, $sp, -4
  sw $s0, -1472($fp)
  li $s0, 44
  addi $sp, $sp, -4
  sw $s1, -1476($fp)
  li $s1, 4
  addi $sp, $sp, -4
  sw $s2, -1480($fp)
  mul $s2, $s0, $s1
  addi $sp, $sp, -4
  sw $s3, -1484($fp)
  add $s3, $t1, $s2
  addi $sp, $sp, -4
  sw $s4, -1488($fp)
  li $s4, 26
  sw $s4, 0($s3)
  addi $sp, $sp, -4
  sw $s5, -1492($fp)
  lw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $s6, -1496($fp)
  li $s6, 45
  addi $sp, $sp, -4
  sw $s7, -1500($fp)
  li $s7, 4
  addi $sp, $sp, -4
  sw $t0, -1504($fp)
  mul $t0, $s6, $s7
  addi $sp, $sp, -4
  sw $t2, -1508($fp)
  lw $t2, -480($fp)
  add $t1, $t2, $t0
  addi $sp, $sp, -4
  sw $t3, -1512($fp)
  li $t3, 83
  sw $t3, 0($t1)
  addi $sp, $sp, -4
  sw $t4, -1516($fp)
  lw $t4, 0($t1)
  addi $sp, $sp, -4
  sw $t5, -1520($fp)
  li $t5, 46
  addi $sp, $sp, -4
  sw $t6, -1524($fp)
  li $t6, 4
  addi $sp, $sp, -4
  sw $t7, -1528($fp)
  mul $t7, $t5, $t6
  addi $sp, $sp, -4
  sw $t8, -1532($fp)
  add $t8, $t2, $t7
  addi $sp, $sp, -4
  sw $t9, -1536($fp)
  li $t9, 53
  sw $t9, 0($t8)
  addi $sp, $sp, -4
  sw $s0, -1540($fp)
  lw $s0, 0($t8)
  addi $sp, $sp, -4
  sw $s1, -1544($fp)
  li $s1, 47
  addi $sp, $sp, -4
  sw $s2, -1548($fp)
  li $s2, 4
  addi $sp, $sp, -4
  sw $s3, -1552($fp)
  mul $s3, $s1, $s2
  addi $sp, $sp, -4
  sw $s4, -1556($fp)
  add $s4, $t2, $s3
  addi $sp, $sp, -4
  sw $s5, -1560($fp)
  li $s5, 5
  sw $s5, 0($s4)
  addi $sp, $sp, -4
  sw $s6, -1564($fp)
  lw $s6, 0($s4)
  addi $sp, $sp, -4
  sw $s7, -1568($fp)
  li $s7, 48
  addi $sp, $sp, -4
  sw $t0, -1572($fp)
  li $t0, 4
  addi $sp, $sp, -4
  sw $t1, -1576($fp)
  mul $t1, $s7, $t0
  addi $sp, $sp, -4
  sw $t3, -1580($fp)
  lw $t3, -480($fp)
  add $t2, $t3, $t1
  addi $sp, $sp, -4
  sw $t4, -1584($fp)
  li $t4, 43
  sw $t4, 0($t2)
  addi $sp, $sp, -4
  sw $t5, -1588($fp)
  lw $t5, 0($t2)
  addi $sp, $sp, -4
  sw $t6, -1592($fp)
  li $t6, 49
  addi $sp, $sp, -4
  sw $t7, -1596($fp)
  li $t7, 4
  addi $sp, $sp, -4
  sw $t8, -1600($fp)
  mul $t8, $t6, $t7
  addi $sp, $sp, -4
  sw $t9, -1604($fp)
  add $t9, $t3, $t8
  addi $sp, $sp, -4
  sw $s0, -1608($fp)
  li $s0, 67
  sw $s0, 0($t9)
  addi $sp, $sp, -4
  sw $s1, -1612($fp)
  lw $s1, 0($t9)
  addi $sp, $sp, -4
  sw $s2, -1616($fp)
  li $s2, 50
  addi $sp, $sp, -4
  sw $s3, -1620($fp)
  li $s3, 4
  addi $sp, $sp, -4
  sw $s4, -1624($fp)
  mul $s4, $s2, $s3
  addi $sp, $sp, -4
  sw $s5, -1628($fp)
  add $s5, $t3, $s4
  addi $sp, $sp, -4
  sw $s6, -1632($fp)
  li $s6, 88
  sw $s6, 0($s5)
  addi $sp, $sp, -4
  sw $s7, -1636($fp)
  lw $s7, 0($s5)
  addi $sp, $sp, -4
  sw $t0, -1640($fp)
  li $t0, 51
  addi $sp, $sp, -4
  sw $t1, -1644($fp)
  li $t1, 4
  addi $sp, $sp, -4
  sw $t2, -1648($fp)
  mul $t2, $t0, $t1
  addi $sp, $sp, -4
  sw $t4, -1652($fp)
  lw $t4, -480($fp)
  add $t3, $t4, $t2
  addi $sp, $sp, -4
  sw $t5, -1656($fp)
  li $t5, 70
  sw $t5, 0($t3)
  addi $sp, $sp, -4
  sw $t6, -1660($fp)
  lw $t6, 0($t3)
  addi $sp, $sp, -4
  sw $t7, -1664($fp)
  li $t7, 52
  addi $sp, $sp, -4
  sw $t8, -1668($fp)
  li $t8, 4
  addi $sp, $sp, -4
  sw $t9, -1672($fp)
  mul $t9, $t7, $t8
  addi $sp, $sp, -4
  sw $s0, -1676($fp)
  add $s0, $t4, $t9
  addi $sp, $sp, -4
  sw $s1, -1680($fp)
  li $s1, 76
  sw $s1, 0($s0)
  addi $sp, $sp, -4
  sw $s2, -1684($fp)
  lw $s2, 0($s0)
  addi $sp, $sp, -4
  sw $s3, -1688($fp)
  li $s3, 53
  addi $sp, $sp, -4
  sw $s4, -1692($fp)
  li $s4, 4
  addi $sp, $sp, -4
  sw $s5, -1696($fp)
  mul $s5, $s3, $s4
  addi $sp, $sp, -4
  sw $s6, -1700($fp)
  add $s6, $t4, $s5
  addi $sp, $sp, -4
  sw $s7, -1704($fp)
  li $s7, 92
  sw $s7, 0($s6)
  addi $sp, $sp, -4
  sw $t0, -1708($fp)
  lw $t0, 0($s6)
  addi $sp, $sp, -4
  sw $t1, -1712($fp)
  li $t1, 54
  addi $sp, $sp, -4
  sw $t2, -1716($fp)
  li $t2, 4
  addi $sp, $sp, -4
  sw $t3, -1720($fp)
  mul $t3, $t1, $t2
  addi $sp, $sp, -4
  sw $t5, -1724($fp)
  lw $t5, -480($fp)
  add $t4, $t5, $t3
  addi $sp, $sp, -4
  sw $t6, -1728($fp)
  li $t6, 94
  sw $t6, 0($t4)
  addi $sp, $sp, -4
  sw $t7, -1732($fp)
  lw $t7, 0($t4)
  addi $sp, $sp, -4
  sw $t8, -1736($fp)
  li $t8, 55
  addi $sp, $sp, -4
  sw $t9, -1740($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -1744($fp)
  mul $s0, $t8, $t9
  addi $sp, $sp, -4
  sw $s1, -1748($fp)
  add $s1, $t5, $s0
  addi $sp, $sp, -4
  sw $s2, -1752($fp)
  li $s2, 48
  sw $s2, 0($s1)
  addi $sp, $sp, -4
  sw $s3, -1756($fp)
  lw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $s4, -1760($fp)
  li $s4, 56
  addi $sp, $sp, -4
  sw $s5, -1764($fp)
  li $s5, 4
  addi $sp, $sp, -4
  sw $s6, -1768($fp)
  mul $s6, $s4, $s5
  addi $sp, $sp, -4
  sw $s7, -1772($fp)
  add $s7, $t5, $s6
  addi $sp, $sp, -4
  sw $t0, -1776($fp)
  li $t0, 34
  sw $t0, 0($s7)
  addi $sp, $sp, -4
  sw $t1, -1780($fp)
  lw $t1, 0($s7)
  addi $sp, $sp, -4
  sw $t2, -1784($fp)
  li $t2, 57
  addi $sp, $sp, -4
  sw $t3, -1788($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -1792($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t6, -1796($fp)
  lw $t6, -480($fp)
  add $t5, $t6, $t4
  addi $sp, $sp, -4
  sw $t7, -1800($fp)
  li $t7, 49
  sw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -1804($fp)
  lw $t8, 0($t5)
  addi $sp, $sp, -4
  sw $t9, -1808($fp)
  li $t9, 58
  addi $sp, $sp, -4
  sw $s0, -1812($fp)
  li $s0, 4
  addi $sp, $sp, -4
  sw $s1, -1816($fp)
  mul $s1, $t9, $s0
  addi $sp, $sp, -4
  sw $s2, -1820($fp)
  add $s2, $t6, $s1
  addi $sp, $sp, -4
  sw $s3, -1824($fp)
  li $s3, 66
  sw $s3, 0($s2)
  addi $sp, $sp, -4
  sw $s4, -1828($fp)
  lw $s4, 0($s2)
  addi $sp, $sp, -4
  sw $s5, -1832($fp)
  li $s5, 59
  addi $sp, $sp, -4
  sw $s6, -1836($fp)
  li $s6, 4
  addi $sp, $sp, -4
  sw $s7, -1840($fp)
  mul $s7, $s5, $s6
  addi $sp, $sp, -4
  sw $t0, -1844($fp)
  add $t0, $t6, $s7
  addi $sp, $sp, -4
  sw $t1, -1848($fp)
  li $t1, 95
  sw $t1, 0($t0)
  addi $sp, $sp, -4
  sw $t2, -1852($fp)
  lw $t2, 0($t0)
  addi $sp, $sp, -4
  sw $t3, -1856($fp)
  li $t3, 60
  addi $sp, $sp, -4
  sw $t4, -1860($fp)
  li $t4, 4
  addi $sp, $sp, -4
  sw $t5, -1864($fp)
  mul $t5, $t3, $t4
  addi $sp, $sp, -4
  sw $t7, -1868($fp)
  lw $t7, -480($fp)
  add $t6, $t7, $t5
  addi $sp, $sp, -4
  sw $t8, -1872($fp)
  li $t8, 78
  sw $t8, 0($t6)
  addi $sp, $sp, -4
  sw $t9, -1876($fp)
  lw $t9, 0($t6)
  addi $sp, $sp, -4
  sw $s0, -1880($fp)
  li $s0, 61
  addi $sp, $sp, -4
  sw $s1, -1884($fp)
  li $s1, 4
  addi $sp, $sp, -4
  sw $s2, -1888($fp)
  mul $s2, $s0, $s1
  addi $sp, $sp, -4
  sw $s3, -1892($fp)
  add $s3, $t7, $s2
  addi $sp, $sp, -4
  sw $s4, -1896($fp)
  li $s4, 62
  sw $s4, 0($s3)
  addi $sp, $sp, -4
  sw $s5, -1900($fp)
  lw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $s6, -1904($fp)
  li $s6, 62
  addi $sp, $sp, -4
  sw $s7, -1908($fp)
  li $s7, 4
  addi $sp, $sp, -4
  sw $t0, -1912($fp)
  mul $t0, $s6, $s7
  addi $sp, $sp, -4
  sw $t1, -1916($fp)
  add $t1, $t7, $t0
  addi $sp, $sp, -4
  sw $t2, -1920($fp)
  li $t2, 32
  sw $t2, 0($t1)
  addi $sp, $sp, -4
  sw $t3, -1924($fp)
  lw $t3, 0($t1)
  addi $sp, $sp, -4
  sw $t4, -1928($fp)
  li $t4, 63
  addi $sp, $sp, -4
  sw $t5, -1932($fp)
  li $t5, 4
  addi $sp, $sp, -4
  sw $t6, -1936($fp)
  mul $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $t8, -1940($fp)
  lw $t8, -480($fp)
  add $t7, $t8, $t6
  addi $sp, $sp, -4
  sw $t9, -1944($fp)
  li $t9, 52
  sw $t9, 0($t7)
  addi $sp, $sp, -4
  sw $s0, -1948($fp)
  lw $s0, 0($t7)
  addi $sp, $sp, -4
  sw $s1, -1952($fp)
  li $s1, 64
  addi $sp, $sp, -4
  sw $s2, -1956($fp)
  li $s2, 4
  addi $sp, $sp, -4
  sw $s3, -1960($fp)
  mul $s3, $s1, $s2
  addi $sp, $sp, -4
  sw $s4, -1964($fp)
  add $s4, $t8, $s3
  addi $sp, $sp, -4
  sw $s5, -1968($fp)
  li $s5, 16
  sw $s5, 0($s4)
  addi $sp, $sp, -4
  sw $s6, -1972($fp)
  lw $s6, 0($s4)
  addi $sp, $sp, -4
  sw $s7, -1976($fp)
  li $s7, 65
  addi $sp, $sp, -4
  sw $t0, -1980($fp)
  li $t0, 4
  addi $sp, $sp, -4
  sw $t1, -1984($fp)
  mul $t1, $s7, $t0
  addi $sp, $sp, -4
  sw $t2, -1988($fp)
  add $t2, $t8, $t1
  addi $sp, $sp, -4
  sw $t3, -1992($fp)
  li $t3, 72
  sw $t3, 0($t2)
  addi $sp, $sp, -4
  sw $t4, -1996($fp)
  lw $t4, 0($t2)
  addi $sp, $sp, -4
  sw $t5, -2000($fp)
  li $t5, 66
  addi $sp, $sp, -4
  sw $t6, -2004($fp)
  li $t6, 4
  addi $sp, $sp, -4
  sw $t7, -2008($fp)
  mul $t7, $t5, $t6
  addi $sp, $sp, -4
  sw $t9, -2012($fp)
  lw $t9, -480($fp)
  add $t8, $t9, $t7
  addi $sp, $sp, -4
  sw $s0, -2016($fp)
  li $s0, 27
  sw $s0, 0($t8)
  addi $sp, $sp, -4
  sw $s1, -2020($fp)
  lw $s1, 0($t8)
  addi $sp, $sp, -4
  sw $s2, -2024($fp)
  li $s2, 67
  addi $sp, $sp, -4
  sw $s3, -2028($fp)
  li $s3, 4
  addi $sp, $sp, -4
  sw $s4, -2032($fp)
  mul $s4, $s2, $s3
  addi $sp, $sp, -4
  sw $s5, -2036($fp)
  add $s5, $t9, $s4
  addi $sp, $sp, -4
  sw $s6, -2040($fp)
  li $s6, 28
  sw $s6, 0($s5)
  addi $sp, $sp, -4
  sw $s7, -2044($fp)
  lw $s7, 0($s5)
  addi $sp, $sp, -4
  sw $t0, -2048($fp)
  li $t0, 68
  addi $sp, $sp, -4
  sw $t1, -2052($fp)
  li $t1, 4
  addi $sp, $sp, -4
  sw $t2, -2056($fp)
  mul $t2, $t0, $t1
  addi $sp, $sp, -4
  sw $t3, -2060($fp)
  add $t3, $t9, $t2
  addi $sp, $sp, -4
  sw $t4, -2064($fp)
  li $t4, 22
  sw $t4, 0($t3)
  addi $sp, $sp, -4
  sw $t5, -2068($fp)
  lw $t5, 0($t3)
  addi $sp, $sp, -4
  sw $t6, -2072($fp)
  li $t6, 69
  addi $sp, $sp, -4
  sw $t7, -2076($fp)
  li $t7, 4
  addi $sp, $sp, -4
  sw $t8, -2080($fp)
  mul $t8, $t6, $t7
  addi $sp, $sp, -4
  sw $s0, -2084($fp)
  lw $s0, -480($fp)
  add $t9, $s0, $t8
  addi $sp, $sp, -4
  sw $s1, -2088($fp)
  li $s1, 40
  sw $s1, 0($t9)
  addi $sp, $sp, -4
  sw $s2, -2092($fp)
  lw $s2, 0($t9)
  addi $sp, $sp, -4
  sw $s3, -2096($fp)
  li $s3, 70
  addi $sp, $sp, -4
  sw $s4, -2100($fp)
  li $s4, 4
  addi $sp, $sp, -4
  sw $s5, -2104($fp)
  mul $s5, $s3, $s4
  addi $sp, $sp, -4
  sw $s6, -2108($fp)
  add $s6, $s0, $s5
  addi $sp, $sp, -4
  sw $s7, -2112($fp)
  li $s7, 84
  sw $s7, 0($s6)
  addi $sp, $sp, -4
  sw $t0, -2116($fp)
  lw $t0, 0($s6)
  addi $sp, $sp, -4
  sw $t1, -2120($fp)
  li $t1, 71
  addi $sp, $sp, -4
  sw $t2, -2124($fp)
  li $t2, 4
  addi $sp, $sp, -4
  sw $t3, -2128($fp)
  mul $t3, $t1, $t2
  addi $sp, $sp, -4
  sw $t4, -2132($fp)
  add $t4, $s0, $t3
  addi $sp, $sp, -4
  sw $t5, -2136($fp)
  li $t5, 91
  sw $t5, 0($t4)
  addi $sp, $sp, -4
  sw $t6, -2140($fp)
  lw $t6, 0($t4)
  addi $sp, $sp, -4
  sw $t7, -2144($fp)
  li $t7, 72
  addi $sp, $sp, -4
  sw $t8, -2148($fp)
  li $t8, 4
  addi $sp, $sp, -4
  sw $t9, -2152($fp)
  mul $t9, $t7, $t8
  addi $sp, $sp, -4
  sw $s1, -2156($fp)
  lw $s1, -480($fp)
  add $s0, $s1, $t9
  addi $sp, $sp, -4
  sw $s2, -2160($fp)
  li $s2, 96
  sw $s2, 0($s0)
  addi $sp, $sp, -4
  sw $s3, -2164($fp)
  lw $s3, 0($s0)
  addi $sp, $sp, -4
  sw $s4, -2168($fp)
  li $s4, 73
  addi $sp, $sp, -4
  sw $s5, -2172($fp)
  li $s5, 4
  addi $sp, $sp, -4
  sw $s6, -2176($fp)
  mul $s6, $s4, $s5
  addi $sp, $sp, -4
  sw $s7, -2180($fp)
  add $s7, $s1, $s6
  addi $sp, $sp, -4
  sw $t0, -2184($fp)
  li $t0, 57
  sw $t0, 0($s7)
  addi $sp, $sp, -4
  sw $t1, -2188($fp)
  lw $t1, 0($s7)
  addi $sp, $sp, -4
  sw $t2, -2192($fp)
  li $t2, 74
  addi $sp, $sp, -4
  sw $t3, -2196($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -2200($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t5, -2204($fp)
  add $t5, $s1, $t4
  addi $sp, $sp, -4
  sw $t6, -2208($fp)
  li $t6, 87
  sw $t6, 0($t5)
  addi $sp, $sp, -4
  sw $t7, -2212($fp)
  lw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -2216($fp)
  li $t8, 75
  addi $sp, $sp, -4
  sw $t9, -2220($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -2224($fp)
  mul $s0, $t8, $t9
  addi $sp, $sp, -4
  sw $s2, -2228($fp)
  lw $s2, -480($fp)
  add $s1, $s2, $s0
  addi $sp, $sp, -4
  sw $s3, -2232($fp)
  li $s3, 51
  sw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $s4, -2236($fp)
  lw $s4, 0($s1)
  addi $sp, $sp, -4
  sw $s5, -2240($fp)
  li $s5, 76
  addi $sp, $sp, -4
  sw $s6, -2244($fp)
  li $s6, 4
  addi $sp, $sp, -4
  sw $s7, -2248($fp)
  mul $s7, $s5, $s6
  addi $sp, $sp, -4
  sw $t0, -2252($fp)
  add $t0, $s2, $s7
  addi $sp, $sp, -4
  sw $t1, -2256($fp)
  li $t1, 98
  sw $t1, 0($t0)
  addi $sp, $sp, -4
  sw $t2, -2260($fp)
  lw $t2, 0($t0)
  addi $sp, $sp, -4
  sw $t3, -2264($fp)
  li $t3, 77
  addi $sp, $sp, -4
  sw $t4, -2268($fp)
  li $t4, 4
  addi $sp, $sp, -4
  sw $t5, -2272($fp)
  mul $t5, $t3, $t4
  addi $sp, $sp, -4
  sw $t6, -2276($fp)
  add $t6, $s2, $t5
  addi $sp, $sp, -4
  sw $t7, -2280($fp)
  li $t7, 1
  sw $t7, 0($t6)
  addi $sp, $sp, -4
  sw $t8, -2284($fp)
  lw $t8, 0($t6)
  addi $sp, $sp, -4
  sw $t9, -2288($fp)
  li $t9, 78
  addi $sp, $sp, -4
  sw $s0, -2292($fp)
  li $s0, 4
  addi $sp, $sp, -4
  sw $s1, -2296($fp)
  mul $s1, $t9, $s0
  addi $sp, $sp, -4
  sw $s3, -2300($fp)
  lw $s3, -480($fp)
  add $s2, $s3, $s1
  addi $sp, $sp, -4
  sw $s4, -2304($fp)
  li $s4, 10
  sw $s4, 0($s2)
  addi $sp, $sp, -4
  sw $s5, -2308($fp)
  lw $s5, 0($s2)
  addi $sp, $sp, -4
  sw $s6, -2312($fp)
  li $s6, 79
  addi $sp, $sp, -4
  sw $s7, -2316($fp)
  li $s7, 4
  addi $sp, $sp, -4
  sw $t0, -2320($fp)
  mul $t0, $s6, $s7
  addi $sp, $sp, -4
  sw $t1, -2324($fp)
  add $t1, $s3, $t0
  addi $sp, $sp, -4
  sw $t2, -2328($fp)
  li $t2, 11
  sw $t2, 0($t1)
  addi $sp, $sp, -4
  sw $t3, -2332($fp)
  lw $t3, 0($t1)
  addi $sp, $sp, -4
  sw $t4, -2336($fp)
  li $t4, 80
  addi $sp, $sp, -4
  sw $t5, -2340($fp)
  li $t5, 4
  addi $sp, $sp, -4
  sw $t6, -2344($fp)
  mul $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $t7, -2348($fp)
  add $t7, $s3, $t6
  addi $sp, $sp, -4
  sw $t8, -2352($fp)
  li $t8, 24
  sw $t8, 0($t7)
  addi $sp, $sp, -4
  sw $t9, -2356($fp)
  lw $t9, 0($t7)
  addi $sp, $sp, -4
  sw $s0, -2360($fp)
  li $s0, 81
  addi $sp, $sp, -4
  sw $s1, -2364($fp)
  li $s1, 4
  addi $sp, $sp, -4
  sw $s2, -2368($fp)
  mul $s2, $s0, $s1
  addi $sp, $sp, -4
  sw $s4, -2372($fp)
  lw $s4, -480($fp)
  add $s3, $s4, $s2
  addi $sp, $sp, -4
  sw $s5, -2376($fp)
  li $s5, 20
  sw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $s6, -2380($fp)
  lw $s6, 0($s3)
  addi $sp, $sp, -4
  sw $s7, -2384($fp)
  li $s7, 82
  addi $sp, $sp, -4
  sw $t0, -2388($fp)
  li $t0, 4
  addi $sp, $sp, -4
  sw $t1, -2392($fp)
  mul $t1, $s7, $t0
  addi $sp, $sp, -4
  sw $t2, -2396($fp)
  add $t2, $s4, $t1
  addi $sp, $sp, -4
  sw $t3, -2400($fp)
  li $t3, 19
  sw $t3, 0($t2)
  addi $sp, $sp, -4
  sw $t4, -2404($fp)
  lw $t4, 0($t2)
  addi $sp, $sp, -4
  sw $t5, -2408($fp)
  li $t5, 83
  addi $sp, $sp, -4
  sw $t6, -2412($fp)
  li $t6, 4
  addi $sp, $sp, -4
  sw $t7, -2416($fp)
  mul $t7, $t5, $t6
  addi $sp, $sp, -4
  sw $t8, -2420($fp)
  add $t8, $s4, $t7
  addi $sp, $sp, -4
  sw $t9, -2424($fp)
  li $t9, 31
  sw $t9, 0($t8)
  addi $sp, $sp, -4
  sw $s0, -2428($fp)
  lw $s0, 0($t8)
  addi $sp, $sp, -4
  sw $s1, -2432($fp)
  li $s1, 84
  addi $sp, $sp, -4
  sw $s2, -2436($fp)
  li $s2, 4
  addi $sp, $sp, -4
  sw $s3, -2440($fp)
  mul $s3, $s1, $s2
  addi $sp, $sp, -4
  sw $s5, -2444($fp)
  lw $s5, -480($fp)
  add $s4, $s5, $s3
  addi $sp, $sp, -4
  sw $s6, -2448($fp)
  li $s6, 7
  sw $s6, 0($s4)
  addi $sp, $sp, -4
  sw $s7, -2452($fp)
  lw $s7, 0($s4)
  addi $sp, $sp, -4
  sw $t0, -2456($fp)
  li $t0, 85
  addi $sp, $sp, -4
  sw $t1, -2460($fp)
  li $t1, 4
  addi $sp, $sp, -4
  sw $t2, -2464($fp)
  mul $t2, $t0, $t1
  addi $sp, $sp, -4
  sw $t3, -2468($fp)
  add $t3, $s5, $t2
  addi $sp, $sp, -4
  sw $t4, -2472($fp)
  li $t4, 97
  sw $t4, 0($t3)
  addi $sp, $sp, -4
  sw $t5, -2476($fp)
  lw $t5, 0($t3)
  addi $sp, $sp, -4
  sw $t6, -2480($fp)
  li $t6, 86
  addi $sp, $sp, -4
  sw $t7, -2484($fp)
  li $t7, 4
  addi $sp, $sp, -4
  sw $t8, -2488($fp)
  mul $t8, $t6, $t7
  addi $sp, $sp, -4
  sw $t9, -2492($fp)
  add $t9, $s5, $t8
  addi $sp, $sp, -4
  sw $s0, -2496($fp)
  li $s0, 50
  sw $s0, 0($t9)
  addi $sp, $sp, -4
  sw $s1, -2500($fp)
  lw $s1, 0($t9)
  addi $sp, $sp, -4
  sw $s2, -2504($fp)
  li $s2, 87
  addi $sp, $sp, -4
  sw $s3, -2508($fp)
  li $s3, 4
  addi $sp, $sp, -4
  sw $s4, -2512($fp)
  mul $s4, $s2, $s3
  addi $sp, $sp, -4
  sw $s6, -2516($fp)
  lw $s6, -480($fp)
  add $s5, $s6, $s4
  addi $sp, $sp, -4
  sw $s7, -2520($fp)
  li $s7, 86
  sw $s7, 0($s5)
  addi $sp, $sp, -4
  sw $t0, -2524($fp)
  lw $t0, 0($s5)
  addi $sp, $sp, -4
  sw $t1, -2528($fp)
  li $t1, 88
  addi $sp, $sp, -4
  sw $t2, -2532($fp)
  li $t2, 4
  addi $sp, $sp, -4
  sw $t3, -2536($fp)
  mul $t3, $t1, $t2
  addi $sp, $sp, -4
  sw $t4, -2540($fp)
  add $t4, $s6, $t3
  addi $sp, $sp, -4
  sw $t5, -2544($fp)
  li $t5, 79
  sw $t5, 0($t4)
  addi $sp, $sp, -4
  sw $t6, -2548($fp)
  lw $t6, 0($t4)
  addi $sp, $sp, -4
  sw $t7, -2552($fp)
  li $t7, 89
  addi $sp, $sp, -4
  sw $t8, -2556($fp)
  li $t8, 4
  addi $sp, $sp, -4
  sw $t9, -2560($fp)
  mul $t9, $t7, $t8
  addi $sp, $sp, -4
  sw $s0, -2564($fp)
  add $s0, $s6, $t9
  addi $sp, $sp, -4
  sw $s1, -2568($fp)
  li $s1, 17
  sw $s1, 0($s0)
  addi $sp, $sp, -4
  sw $s2, -2572($fp)
  lw $s2, 0($s0)
  addi $sp, $sp, -4
  sw $s3, -2576($fp)
  li $s3, 90
  addi $sp, $sp, -4
  sw $s4, -2580($fp)
  li $s4, 4
  addi $sp, $sp, -4
  sw $s5, -2584($fp)
  mul $s5, $s3, $s4
  addi $sp, $sp, -4
  sw $s7, -2588($fp)
  lw $s7, -480($fp)
  add $s6, $s7, $s5
  addi $sp, $sp, -4
  sw $t0, -2592($fp)
  li $t0, 75
  sw $t0, 0($s6)
  addi $sp, $sp, -4
  sw $t1, -2596($fp)
  lw $t1, 0($s6)
  addi $sp, $sp, -4
  sw $t2, -2600($fp)
  li $t2, 91
  addi $sp, $sp, -4
  sw $t3, -2604($fp)
  li $t3, 4
  addi $sp, $sp, -4
  sw $t4, -2608($fp)
  mul $t4, $t2, $t3
  addi $sp, $sp, -4
  sw $t5, -2612($fp)
  add $t5, $s7, $t4
  addi $sp, $sp, -4
  sw $t6, -2616($fp)
  li $t6, 55
  sw $t6, 0($t5)
  addi $sp, $sp, -4
  sw $t7, -2620($fp)
  lw $t7, 0($t5)
  addi $sp, $sp, -4
  sw $t8, -2624($fp)
  li $t8, 92
  addi $sp, $sp, -4
  sw $t9, -2628($fp)
  li $t9, 4
  addi $sp, $sp, -4
  sw $s0, -2632($fp)
  mul $s0, $t8, $t9
  addi $sp, $sp, -4
  sw $s1, -2636($fp)
  add $s1, $s7, $s0
  addi $sp, $sp, -4
  sw $s2, -2640($fp)
  li $s2, 93
  sw $s2, 0($s1)
  addi $sp, $sp, -4
  sw $s3, -2644($fp)
  lw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $s4, -2648($fp)
  li $s4, 93
  addi $sp, $sp, -4
  sw $s5, -2652($fp)
  li $s5, 4
  addi $sp, $sp, -4
  sw $s6, -2656($fp)
  mul $s6, $s4, $s5
  addi $sp, $sp, -4
  sw $t0, -2660($fp)
  lw $t0, -480($fp)
  add $s7, $t0, $s6
  addi $sp, $sp, -4
  sw $t1, -2664($fp)
  li $t1, 44
  sw $t1, 0($s7)
  addi $sp, $sp, -4
  sw $t2, -2668($fp)
  lw $t2, 0($s7)
  addi $sp, $sp, -4
  sw $t3, -2672($fp)
  li $t3, 94
  addi $sp, $sp, -4
  sw $t4, -2676($fp)
  li $t4, 4
  addi $sp, $sp, -4
  sw $t5, -2680($fp)
  mul $t5, $t3, $t4
  addi $sp, $sp, -4
  sw $t6, -2684($fp)
  add $t6, $t0, $t5
  addi $sp, $sp, -4
  sw $t7, -2688($fp)
  li $t7, 58
  sw $t7, 0($t6)
  addi $sp, $sp, -4
  sw $t8, -2692($fp)
  lw $t8, 0($t6)
  addi $sp, $sp, -4
  sw $t9, -2696($fp)
  li $t9, 95
  addi $sp, $sp, -4
  sw $s0, -2700($fp)
  li $s0, 4
  addi $sp, $sp, -4
  sw $s1, -2704($fp)
  mul $s1, $t9, $s0
  addi $sp, $sp, -4
  sw $s2, -2708($fp)
  add $s2, $t0, $s1
  addi $sp, $sp, -4
  sw $s3, -2712($fp)
  li $s3, 54
  sw $s3, 0($s2)
  addi $sp, $sp, -4
  sw $s4, -2716($fp)
  lw $s4, 0($s2)
  addi $sp, $sp, -4
  sw $s5, -2720($fp)
  li $s5, 96
  addi $sp, $sp, -4
  sw $s6, -2724($fp)
  li $s6, 4
  addi $sp, $sp, -4
  sw $s7, -2728($fp)
  mul $s7, $s5, $s6
  addi $sp, $sp, -4
  sw $t1, -2732($fp)
  lw $t1, -480($fp)
  add $t0, $t1, $s7
  addi $sp, $sp, -4
  sw $t2, -2736($fp)
  li $t2, 45
  sw $t2, 0($t0)
  addi $sp, $sp, -4
  sw $t3, -2740($fp)
  lw $t3, 0($t0)
  addi $sp, $sp, -4
  sw $t4, -2744($fp)
  li $t4, 97
  addi $sp, $sp, -4
  sw $t5, -2748($fp)
  li $t5, 4
  addi $sp, $sp, -4
  sw $t6, -2752($fp)
  mul $t6, $t4, $t5
  addi $sp, $sp, -4
  sw $t7, -2756($fp)
  add $t7, $t1, $t6
  addi $sp, $sp, -4
  sw $t8, -2760($fp)
  li $t8, 41
  sw $t8, 0($t7)
  addi $sp, $sp, -4
  sw $t9, -2764($fp)
  lw $t9, 0($t7)
  addi $sp, $sp, -4
  sw $s0, -2768($fp)
  li $s0, 98
  addi $sp, $sp, -4
  sw $s1, -2772($fp)
  li $s1, 4
  addi $sp, $sp, -4
  sw $s2, -2776($fp)
  mul $s2, $s0, $s1
  addi $sp, $sp, -4
  sw $s3, -2780($fp)
  add $s3, $t1, $s2
  addi $sp, $sp, -4
  sw $s4, -2784($fp)
  li $s4, 90
  sw $s4, 0($s3)
  addi $sp, $sp, -4
  sw $s5, -2788($fp)
  lw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $s6, -2792($fp)
  li $s6, 99
  addi $sp, $sp, -4
  sw $s7, -2796($fp)
  li $s7, 4
  addi $sp, $sp, -4
  sw $t0, -2800($fp)
  mul $t0, $s6, $s7
  addi $sp, $sp, -4
  sw $t2, -2804($fp)
  lw $t2, -480($fp)
  add $t1, $t2, $t0
  addi $sp, $sp, -4
  sw $t3, -2808($fp)
  li $t3, 46
  sw $t3, 0($t1)
  addi $sp, $sp, -4
  sw $t4, -2812($fp)
  lw $t4, 0($t1)
  addi $sp, $sp, -4
  sw $t5, -2816($fp)
  li $t5, 0
  addi $sp, $sp, -4
  sw $t6, -2820($fp)
  move $t6, $t5
  addi $sp, $sp, -4
  sw $t7, -2824($fp)
  addi $sp, $sp, -4
  sw $t8, -2828($fp)
  addi $sp, $sp, -4
  sw $t9, -2832($fp)
  addi $sp, $sp, -4
  sw $s0, -2836($fp)
  addi $sp, $sp, -4
  sw $s1, -2840($fp)
  addi $sp, $sp, -4
  sw $s2, -2844($fp)
  addi $sp, $sp, -4
  sw $s3, -2848($fp)
  addi $sp, $sp, -4
  sw $s4, -2852($fp)
  addi $sp, $sp, -4
  sw $s5, -2856($fp)
  addi $sp, $sp, -4
  sw $s6, -2860($fp)
  addi $sp, $sp, -4
  sw $s7, -2864($fp)
  addi $sp, $sp, -4
  sw $t0, -2868($fp)
  addi $sp, $sp, -4
  sw $t1, -2872($fp)
  addi $sp, $sp, -4
  sw $t3, -2876($fp)
  addi $sp, $sp, -4
  sw $t4, -2880($fp)
  addi $sp, $sp, -4
  sw $t5, -2884($fp)
  addi $sp, $sp, -4
  sw $t6, -2888($fp)
label1:
  li $t7, 1
  lw $t9, -476($fp)
  sub $t8, $t9, $t7
  addi $sp, $sp, -4
  sw $t7, -2892($fp)
  addi $sp, $sp, -4
  sw $t8, -2896($fp)
  lw $s0, -2884($fp)
  lw $s1, -2896($fp)
  blt $s0, $s1, label2
  j label3
label2:
  lw $s3, -2884($fp)
  move $s2, $s3
  move $s4, $s2
  li $s5, 1
  add $s6, $s3, $s5
  move $s7, $s6
  move $t0, $s7
  addi $sp, $sp, -4
  sw $s2, -2900($fp)
  addi $sp, $sp, -4
  sw $s4, -2904($fp)
  addi $sp, $sp, -4
  sw $s5, -2908($fp)
  addi $sp, $sp, -4
  sw $s6, -2912($fp)
  addi $sp, $sp, -4
  sw $s7, -2916($fp)
  addi $sp, $sp, -4
  sw $t0, -2920($fp)
label4:
  lw $t1, -2916($fp)
  lw $t2, -476($fp)
  blt $t1, $t2, label5
  j label6
label5:
  li $t3, 4
  lw $t5, -2916($fp)
  mul $t4, $t5, $t3
  lw $t7, -480($fp)
  add $t6, $t7, $t4
  li $t8, 4
  lw $s0, -2900($fp)
  mul $t9, $s0, $t8
  add $s1, $t7, $t9
  lw $s2, 0($t6)
  lw $s3, 0($s1)
  addi $sp, $sp, -4
  sw $t3, -2924($fp)
  addi $sp, $sp, -4
  sw $t4, -2928($fp)
  addi $sp, $sp, -4
  sw $t6, -2932($fp)
  addi $sp, $sp, -4
  sw $t8, -2936($fp)
  addi $sp, $sp, -4
  sw $t9, -2940($fp)
  addi $sp, $sp, -4
  sw $s1, -2944($fp)
  addi $sp, $sp, -4
  sw $s2, -2948($fp)
  addi $sp, $sp, -4
  sw $s3, -2952($fp)
  blt $s2, $s3, label7
  j label8
label7:
  lw $s4, -2900($fp)
  lw $s5, -2916($fp)
  move $s4, $s5
  move $s6, $s4
  sw $s4, -2900($fp)
  addi $sp, $sp, -4
  sw $s6, -2956($fp)
label8:
  li $s7, 1
  lw $t1, -2916($fp)
  add $t0, $t1, $s7
  move $t1, $t0
  move $t2, $t1
  addi $sp, $sp, -4
  sw $s7, -2960($fp)
  addi $sp, $sp, -4
  sw $t0, -2964($fp)
  sw $t1, -2916($fp)
  addi $sp, $sp, -4
  sw $t2, -2968($fp)
  j label4
label6:
  li $t3, 4
  lw $t5, -2884($fp)
  mul $t4, $t5, $t3
  lw $t7, -480($fp)
  add $t6, $t7, $t4
  lw $t8, 0($t6)
  move $t9, $t8
  li $s0, 4
  mul $s1, $t5, $s0
  add $s2, $t7, $s1
  li $s3, 4
  lw $s5, -2900($fp)
  mul $s4, $s5, $s3
  add $s6, $t7, $s4
  lw $s7, 0($s6)
  sw $s7, 0($s2)
  lw $t0, 0($s2)
  li $t1, 4
  mul $t2, $s5, $t1
  addi $sp, $sp, -4
  sw $t3, -2972($fp)
  add $t3, $t7, $t2
  sw $t8, 0($t3)
  addi $sp, $sp, -4
  sw $t4, -2976($fp)
  lw $t4, 0($t3)
  li $t5, 1
  addi $sp, $sp, -4
  sw $t6, -2980($fp)
  lw $t7, -2884($fp)
  add $t6, $t7, $t5
  move $t7, $t6
  addi $sp, $sp, -4
  sw $t8, -2984($fp)
  move $t8, $t7
  addi $sp, $sp, -4
  sw $t9, -2988($fp)
  addi $sp, $sp, -4
  sw $s0, -2992($fp)
  addi $sp, $sp, -4
  sw $s1, -2996($fp)
  addi $sp, $sp, -4
  sw $s2, -3000($fp)
  addi $sp, $sp, -4
  sw $s3, -3004($fp)
  addi $sp, $sp, -4
  sw $s4, -3008($fp)
  addi $sp, $sp, -4
  sw $s6, -3012($fp)
  addi $sp, $sp, -4
  sw $s7, -3016($fp)
  addi $sp, $sp, -4
  sw $t0, -3020($fp)
  addi $sp, $sp, -4
  sw $t1, -3024($fp)
  addi $sp, $sp, -4
  sw $t2, -3028($fp)
  addi $sp, $sp, -4
  sw $t3, -3032($fp)
  addi $sp, $sp, -4
  sw $t4, -3036($fp)
  addi $sp, $sp, -4
  sw $t5, -3040($fp)
  addi $sp, $sp, -4
  sw $t6, -3044($fp)
  sw $t7, -2884($fp)
  addi $sp, $sp, -4
  sw $t8, -3048($fp)
  j label1
label3:
  lw $t9, -2884($fp)
  li $t9, 0
  move $s0, $t9
  sw $t9, -2884($fp)
  addi $sp, $sp, -4
  sw $s0, -3052($fp)
label9:
  lw $s1, -2884($fp)
  lw $s2, -476($fp)
  blt $s1, $s2, label10
  j label11
label10:
  li $s3, 4
  lw $s5, -2884($fp)
  mul $s4, $s5, $s3
  lw $s7, -480($fp)
  add $s6, $s7, $s4
  lw $t0, 0($s6)
  addi $sp, $sp, -4
  sw $s3, -3056($fp)
  addi $sp, $sp, -4
  sw $s4, -3060($fp)
  addi $sp, $sp, -4
  sw $s6, -3064($fp)
  addi $sp, $sp, -4
  sw $t0, -3068($fp)
  lw $t1, -2884($fp)
  bne $t0, $t1, label12
  j label13
label12:
  li $t2, 1
  move $a0, $t2
  jal write
  li $v0, 1
  addi $sp, $sp, -4
  sw $t2, -3072($fp)
  lw $t0, -404($fp)
  lw $t1, -408($fp)
  lw $t2, -412($fp)
  lw $t3, -416($fp)
  lw $t4, -420($fp)
  lw $t5, -424($fp)
  lw $t6, -428($fp)
  lw $t7, -432($fp)
  lw $t8, -436($fp)
  lw $t9, -440($fp)
  lw $s0, -444($fp)
  lw $s1, -448($fp)
  lw $s2, -452($fp)
  lw $s3, -456($fp)
  lw $s4, -460($fp)
  lw $s5, -464($fp)
  lw $s6, -468($fp)
  lw $s7, -472($fp)
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label13:
  li $t0, 1
  lw $t2, -2884($fp)
  add $t1, $t2, $t0
  move $t2, $t1
  move $t3, $t2
  addi $sp, $sp, -4
  sw $t0, -3076($fp)
  addi $sp, $sp, -4
  sw $t1, -3080($fp)
  sw $t2, -2884($fp)
  addi $sp, $sp, -4
  sw $t3, -3084($fp)
  j label9
label11:
  lw $t0, -2884($fp)
  li $t0, 0
  move $t1, $t0
  sw $t0, -2884($fp)
  addi $sp, $sp, -4
  sw $t1, -3088($fp)
label14:
  li $t2, 1
  lw $t0, -476($fp)
  sub $t3, $t0, $t2
  addi $sp, $sp, -4
  sw $t2, -3092($fp)
  addi $sp, $sp, -4
  sw $t3, -3096($fp)
  lw $t1, -2884($fp)
  lw $t2, -3096($fp)
  blt $t1, $t2, label15
  j label16
label15:
  lw $t3, -2900($fp)
  lw $t0, -2884($fp)
  move $t3, $t0
  move $t1, $t3
  li $t2, 1
  add $t4, $t0, $t2
  lw $t5, -2916($fp)
  move $t5, $t4
  move $t6, $t5
  sw $t3, -2900($fp)
  addi $sp, $sp, -4
  sw $t1, -3100($fp)
  addi $sp, $sp, -4
  sw $t2, -3104($fp)
  addi $sp, $sp, -4
  sw $t4, -3108($fp)
  sw $t5, -2916($fp)
  addi $sp, $sp, -4
  sw $t6, -3112($fp)
label17:
  lw $t3, -2916($fp)
  lw $t0, -476($fp)
  blt $t3, $t0, label18
  j label19
label18:
  li $t1, 4
  lw $t4, -2916($fp)
  mul $t2, $t4, $t1
  lw $t6, -480($fp)
  add $t5, $t6, $t2
  li $t3, 4
  lw $t7, -2900($fp)
  mul $t0, $t7, $t3
  add $t8, $t6, $t0
  lw $t9, 0($t5)
  lw $s0, 0($t8)
  addi $sp, $sp, -4
  sw $t1, -3116($fp)
  addi $sp, $sp, -4
  sw $t2, -3120($fp)
  addi $sp, $sp, -4
  sw $t5, -3124($fp)
  addi $sp, $sp, -4
  sw $t3, -3128($fp)
  addi $sp, $sp, -4
  sw $t0, -3132($fp)
  addi $sp, $sp, -4
  sw $t8, -3136($fp)
  addi $sp, $sp, -4
  sw $t9, -3140($fp)
  addi $sp, $sp, -4
  sw $s0, -3144($fp)
  blt $t9, $s0, label20
  j label21
label20:
  lw $t1, -2900($fp)
  lw $t2, -2916($fp)
  move $t1, $t2
  move $t4, $t1
  sw $t1, -2900($fp)
  addi $sp, $sp, -4
  sw $t4, -3148($fp)
label21:
  li $t5, 1
  lw $t3, -2916($fp)
  add $t6, $t3, $t5
  move $t3, $t6
  move $t0, $t3
  addi $sp, $sp, -4
  sw $t5, -3152($fp)
  addi $sp, $sp, -4
  sw $t6, -3156($fp)
  sw $t3, -2916($fp)
  addi $sp, $sp, -4
  sw $t0, -3160($fp)
  j label17
label19:
  li $t7, 4
  lw $t9, -2884($fp)
  mul $t8, $t9, $t7
  lw $t1, -480($fp)
  add $s0, $t1, $t8
  lw $t2, -2984($fp)
  lw $t2, 0($s0)
  move $t4, $t2
  li $t5, 4
  mul $t6, $t9, $t5
  add $t3, $t1, $t6
  li $t0, 4
  lw $s2, -2900($fp)
  mul $s1, $s2, $t0
  add $s3, $t1, $s1
  lw $s4, 0($s3)
  sw $s4, 0($t3)
  lw $s5, 0($t3)
  li $s6, 4
  mul $s7, $s2, $s6
  addi $sp, $sp, -4
  sw $t7, -3164($fp)
  add $t7, $t1, $s7
  sw $t2, 0($t7)
  addi $sp, $sp, -4
  sw $t8, -3168($fp)
  lw $t8, 0($t7)
  li $t9, 1
  addi $sp, $sp, -4
  sw $s0, -3172($fp)
  lw $t1, -2884($fp)
  add $s0, $t1, $t9
  move $t1, $s0
  move $t2, $t1
  addi $sp, $sp, -4
  sw $t4, -3176($fp)
  addi $sp, $sp, -4
  sw $t5, -3180($fp)
  addi $sp, $sp, -4
  sw $t6, -3184($fp)
  addi $sp, $sp, -4
  sw $t3, -3188($fp)
  addi $sp, $sp, -4
  sw $t0, -3192($fp)
  addi $sp, $sp, -4
  sw $s1, -3196($fp)
  addi $sp, $sp, -4
  sw $s3, -3200($fp)
  addi $sp, $sp, -4
  sw $s4, -3204($fp)
  addi $sp, $sp, -4
  sw $s5, -3208($fp)
  addi $sp, $sp, -4
  sw $s6, -3212($fp)
  addi $sp, $sp, -4
  sw $s7, -3216($fp)
  addi $sp, $sp, -4
  sw $t7, -3220($fp)
  addi $sp, $sp, -4
  sw $t8, -3224($fp)
  addi $sp, $sp, -4
  sw $t9, -3228($fp)
  addi $sp, $sp, -4
  sw $s0, -3232($fp)
  sw $t1, -2884($fp)
  addi $sp, $sp, -4
  sw $t2, -3236($fp)
  j label14
label16:
  lw $t4, -2884($fp)
  li $t4, 0
  move $t5, $t4
  sw $t4, -2884($fp)
  addi $sp, $sp, -4
  sw $t5, -3240($fp)
label22:
  lw $t6, -2884($fp)
  lw $t3, -476($fp)
  blt $t6, $t3, label23
  j label24
label23:
  li $t0, 4
  lw $s2, -2884($fp)
  mul $s1, $s2, $t0
  lw $s4, -480($fp)
  add $s3, $s4, $s1
  lw $s5, 0($s3)
  addi $sp, $sp, -4
  sw $t0, -3244($fp)
  addi $sp, $sp, -4
  sw $s1, -3248($fp)
  addi $sp, $sp, -4
  sw $s3, -3252($fp)
  addi $sp, $sp, -4
  sw $s5, -3256($fp)
  lw $s6, -2884($fp)
  bne $s5, $s6, label25
  j label26
label25:
  li $s7, 1
  move $a0, $s7
  jal write
  li $v0, 1
  addi $sp, $sp, -4
  sw $s7, -3260($fp)
  lw $t0, -404($fp)
  lw $t1, -408($fp)
  lw $t2, -412($fp)
  lw $t3, -416($fp)
  lw $t4, -420($fp)
  lw $t5, -424($fp)
  lw $t6, -428($fp)
  lw $t7, -432($fp)
  lw $t8, -436($fp)
  lw $t9, -440($fp)
  lw $s0, -444($fp)
  lw $s1, -448($fp)
  lw $s2, -452($fp)
  lw $s3, -456($fp)
  lw $s4, -460($fp)
  lw $s5, -464($fp)
  lw $s6, -468($fp)
  lw $s7, -472($fp)
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label26:
  li $t0, 1
  lw $t2, -2884($fp)
  add $t1, $t2, $t0
  move $t2, $t1
  move $t3, $t2
  addi $sp, $sp, -4
  sw $t0, -3264($fp)
  addi $sp, $sp, -4
  sw $t1, -3268($fp)
  sw $t2, -2884($fp)
  addi $sp, $sp, -4
  sw $t3, -3272($fp)
  j label22
label24:
  li $t0, 0
  move $a0, $t0
  jal write
  li $v0, 0
  addi $sp, $sp, -4
  sw $t0, -3276($fp)
  lw $t0, -404($fp)
  lw $t1, -408($fp)
  lw $t2, -412($fp)
  lw $t3, -416($fp)
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  lw $ra, 0($sp)
  addi $sp, $sp, 4
