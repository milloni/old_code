#!/bin/bash

echo "0" "$my_var"
echo "1" "${my_var:-value}"
echo "2" "$my_var"
echo "3" "${my_var:=value}"
echo "4" "$my_var"

echo "5" "my_var" "${my_var+exists}"
echo "6" "my_foo" "${my_foo+exists}"

digits="0123456789"
echo "7" "\$digits" "$digits"
echo "8" "\${digits:2:4}" "${digits:2:4}"

echo "9" "$my_foo"
echo "10" "${my_foo:?}"

