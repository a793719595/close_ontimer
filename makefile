Q           :=@  
CC          :=g++  #使用 g++ 编译
SRCS        :=$(wildcard *.cpp)  #利用wildcard函数获得目录下所有的.cpp文件
#SRCS        :=main.cpp
TARGET      :=uvloop
OBJECTS     :=
CFLAGS      :=-I ./include/  ./include/libuv.a       #寻找依赖性时，若不在当前-std=c++11
LDFLAGS     := -ldl -lpthread 
OUTPATH		:=./bin
.PHONY: all
all: clean $(TARGET)
#终极目标是all 需要两个依赖 clean 和 $(TARGET) 会先去完成第一个依赖的任务 所以先执行的是clean: 后的语句

$(TARGET):
	$(Q)echo "  Building '$@' ..."
	$(CC) -g $(SRCS) -std=c++11 -o $@ $(CFLAGS) $(LDFLAGS)
	$(Q)mv $(TARGET) $(OUTPATH)  
    
# $(Q)mv $(TARGET) $(OUTPATH) 移动 GetWinInfo.exe 到./bin目录下
# $(Q) 代表 @ 用来在命令行中不显示该行命令
# -l 链接的库的名字 m是数学库 -m 32生成32位代码 -I 头文件路径 -L动态链接或静态链接路径
.PHONY: clean
clean:
	$(Q)echo "  Cleaning '$(TARGET)' ..."
	$(Q)$(RM) $(TARGET)

# .PHONY：clean 作用是当目录下有clean文件时依旧执行命令