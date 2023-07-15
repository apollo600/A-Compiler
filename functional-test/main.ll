target triple = "x86_64-pc-windows-msys"

@a = global i32 3 align 4 
@b = global i32 5 align 4 

; func def
define i32 @main () {
	%a = load i32, i32* @a, align 4
	%b = load i32, i32* @b, align 4
	%v1 = add i32 %a, %b
	ret i32 %v1
}
