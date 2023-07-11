$compiler = "../front-end/parser.out"
$test_input = $args[0]
$IR = "-o ./main.ll"
$output = $args[1]

Start-Process -FilePath $compiler -ArgumentList $test_input,$IR -RedirectStandardOutput $output -Wait