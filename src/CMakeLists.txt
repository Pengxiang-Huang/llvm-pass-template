# add opt load libarary 
add_llvm_library(MyLegacyPass MODULE
	MyLegacyPass.cpp
)

# install 
install(TARGETS MyLegacyPass 
	LIBRARY DESTINATION lib
)
