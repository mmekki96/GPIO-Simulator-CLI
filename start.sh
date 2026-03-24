prepare_env() {
	if [ $# -ne 0 ]; then
		echo "This script does not support any argument"
		exit 1
	fi

	if [ ! -d build/ ]; then
		echo "[.] Build the project ..."
		make all
		echo "[.] Build complete successfully"
	fi
}

main() {
	prepare_env
	echo "[.] Launching the application ..."
	build/main
}

main
