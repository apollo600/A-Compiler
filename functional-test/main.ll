target triple = "x86_64-pc-windows-msys"


; func def
define i32 @main () {
	%b0 = add i32 0, 0
	%_c = add i32 0, 0
	%v1 = add i32 %b0, %_c
	ret i32 %v1
}
