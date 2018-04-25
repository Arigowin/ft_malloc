#!/bin/sh

if [[ "$OSTYPE" == 'linux-gnu' ]]; then
	export LD_LIBRARY_PATH=.
	export LD_INSERT_LIBRARIES="libft_malloc.so"
else
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES="libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1
fi
$@
