SHELL := /bin/bash
arch=`dpkg --print-architecture`
export version=1.1.1
build:
	# 编译
	mkdir building -p
	
	cd building/ && qmake ..
	cd building/ && make -j$(nproc)

clean:
	rm -rf building
	rm -rf build
	rm -rf /tmp/spark-webapp-runtime-runner

package:
	make build
	#export arch=`arch`
	cp building/spark-webapp-runtime-runner deb/opt/apps/spark-webapp-runtime-runner/spark-webapp-runtime-runner
	cp spark-web-packer  deb/opt/apps/spark-webapp-runtime-runner/
	cp launch.sh deb/opt/apps/spark-webapp-runtime-runner/
	cp information.json deb/opt/apps/spark-webapp-runtime-runner/
	mkdir -p /tmp/spark-webapp-runtime-runner
	cp deb/* /tmp/spark-webapp-runtime-runner -r
	sed -i "s/@@version@@/${version}/g" /tmp/spark-webapp-runtime-runner/DEBIAN/control #> /tmp/spark-webapp-runtime-runner/DEBIAN/control
	sed -i "s/@@arch@@/${arch}/g" /tmp/spark-webapp-runtime-runner/DEBIAN/control #> /tmp/spark-webapp-runtime-runner/DEBIAN/control
	dpkg -b /tmp/spark-webapp-runtime-runner spark-webapp-runtime-runner_${version}_${arch}.deb
	rm -rf /tmp/spark-webapp-runtime-runner
