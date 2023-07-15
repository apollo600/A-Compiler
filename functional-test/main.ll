target triple = "x86_64-pc-windows-msys"

@a = global i32 3 align 4 
@b = global i32 5 align 4 
; func def
define i32 @main () {
	%v1 = add i32 @a , @b 
	ret i32 %v1
}
