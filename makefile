CIPHER_CODE_DIR=cipher_code
DES_DIR=des
INITIAL_REPLACE_DIR=initial_replace
ITERATION_DIR=iteration
REVERSE_REPLACE_DIR=reverse_replace
UTILS_DIR=utils
#INC_DIR = -I${CIPHER_CODE_DIR} \
		  -I${DES_DIR} \
		  -I${INITIAL_REPLACE_DIR} \
		  -I${ITERATION_DIR} \
		  -I${REVERSE_REPLACE_DIR} \
		  -I${UTILS_DIR}

SRC = ${wildcard ${CIPHER_CODE_DIR}/*.cpp} \
	  ${wildcard ${DES_DIR}/*.cpp} \
	  ${wildcard ${INITIAL_REPLACE_DIR}/*.cpp} \
	  ${wildcard ${ITERATION_DIR}/*.cpp} \
	  ${wildcard ${REVERSE_REPLACE_DIR}/*.cpp} \
	  ${wildcard ${UTILS_DIR}/*.cpp} 

OBJ = ${patsubst %.cpp, %.o, ${SRC}}

TARGET=main.exe
FALGS=-std=c++11

${TARGET}: ${OBJ} main.o 
	g++ ${OBJ} main.o -o ${TARGET} ${FALGS}
	@echo "Compile done."

${OBJ}: ${SRC} 
	g++ -c $?
	@mv cipher_code.o ${CIPHER_CODE_DIR}
	@mv des.o ${DES_DIR}
	@mv initial_replace.o ${INITIAL_REPLACE_DIR}
	@mv iteration.o ${ITERATION_DIR}
	@mv reverse_replace.o ${REVERSE_REPLACE_DIR}
	@mv utils.o ${UTILS_DIR}

main.o: main.cpp
	g++ main.cpp -c

clean:
	@rm ${OBJ}
	@rm main.o
	@rm main.exe
	@echo "Clean done."
