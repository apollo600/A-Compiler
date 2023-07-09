$compiler = "../front-end/parser.out"
$test_input = $args[0]
$output = $args[1]

Start-Process -FilePath $compiler -ArgumentList $test_input,$output -RedirectStandardOutput $output -Wait