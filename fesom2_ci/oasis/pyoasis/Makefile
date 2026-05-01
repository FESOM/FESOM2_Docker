PYOASIS=$(COUPLE)/pyoasis


# Doc
doc:
	cd docs && make latexpdf && cp _build/latex/pyoasis.pdf ..

# Test

ifeq ($(PYOASIS),/pyoasis)
PYOASIS := .
endif

test: test-python
test-devel: wrappertest examples examples_f examples_c
test-python: examples examples_f examples_c
test-nopython: examples_f_nopython examples_c_nopython

wrappertest:
	cd $(PYOASIS)/tests && ./run_pytest.sh

examples: example1 example2 example3 example4 example5 example6 example8 example7 example9 example10

example1:
	cd $(PYOASIS)/examples/1-serial/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example2:
	cd $(PYOASIS)/examples/2-apple/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example3:
	cd $(PYOASIS)/examples/3-box/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example4:
	cd $(PYOASIS)/examples/4-orange/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example5:
	cd $(PYOASIS)/examples/5-points/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example6:
	cd $(PYOASIS)/examples/6-apple_and_orange/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example7:
	cd $(PYOASIS)/examples/7-multiple-puts/python && (bash run.sh | tee test_output.txt) && grep -iq "field 2 received successfully at time 40800" test_output.txt && rm -f test_output.txt

example8:
	cd $(PYOASIS)/examples/8-interoperability/fortran_and_python && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example9:
	cd $(PYOASIS)/examples/9-python_fortran_C-multi_intracomm  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example10:
	cd $(PYOASIS)/examples/10-grid/python && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

examples_f: example1_f example2_f example3_f example4_f example5_f example6_f example7_f example8_f example9_f example10_f example11_f
examples_f_nopython: example1_f example2_f example3_f example4_f example5_f example6_f example7_f example10_f example11_f

example1_f:
	cd $(PYOASIS)/examples/1-serial/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example2_f:
	cd $(PYOASIS)/examples/2-apple/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example3_f:
	cd $(PYOASIS)/examples/3-box/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example4_f:
	cd $(PYOASIS)/examples/4-orange/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example5_f:
	cd $(PYOASIS)/examples/5-points/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example6_f:
	cd $(PYOASIS)/examples/6-apple_and_orange/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example7_f:
	cd $(PYOASIS)/examples/7-multiple-puts/fortran && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example8_f:
	cd $(PYOASIS)/examples/8-interoperability/fortran_and_python && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example9_f:
	cd $(PYOASIS)/examples/9-python_fortran_C-multi_intracomm  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example10_f:
	cd $(PYOASIS)/examples/10-grid/fortran  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example11_f:
	cd $(PYOASIS)/examples/11-test-interpolation/fortran  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt


examples_c: example1_c example2_c example3_c example4_c example5_c example6_c example7_c example8_c example9_c example10_c example11_c
examples_c_nopython: example1_c example2_c example3_c example4_c example5_c example6_c example7_c example8_c example10_c example11_c

example1_c:
	cd $(PYOASIS)/examples/1-serial/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example2_c:
	cd $(PYOASIS)/examples/2-apple/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example3_c:
	cd $(PYOASIS)/examples/3-box/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example4_c:
	cd $(PYOASIS)/examples/4-orange/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example5_c:
	cd $(PYOASIS)/examples/5-points/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example6_c:
	cd $(PYOASIS)/examples/6-apple_and_orange/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example7_c:
	cd $(PYOASIS)/examples/7-multiple-puts/C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example8_c:
	cd $(PYOASIS)/examples/8-interoperability/fortran_and_C && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example9_c:
	cd $(PYOASIS)/examples/9-python_fortran_C-multi_intracomm  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example10_c:
	cd $(PYOASIS)/examples/10-grid/C  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt

example11_c:
	cd $(PYOASIS)/examples/11-test-interpolation/C  && make clean && (bash run.sh | tee test_output.txt) && grep -iq "successfully" test_output.txt && rm -f test_output.txt
