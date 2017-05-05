" --------------------------------------------------------------------
" Owner: 王涵
" Email: daoshuti@163.com
" Github: https://github.com/daoshuti
" --------------------------------------------------------------------
" GENERAL SETTINGS:
" --------------------------------------------------------------------
"  {{{1
" To use VIM settings, out of VI compatible mode.
set nocompatible
" Enable file type detection.
filetype plugin indent on " 开启三个功能：文件类型检查、插件、缩进
" Syntax highlighting.
syntax on
" Setting colorscheme
" colorscheme industry " 配色主题的名称设置为industry
set   background=dark " 配色主题的色系设置为dark
" Other settings.
set   autoindent 	" 创建新行自动缩进
set   autoread 		" 文件在Vim之外修改过，自动重新读入
set   autowrite
set   backspace=indent,eol,start
set   nobackup
set   cindent 		" 开启针对c文件的缩进
set   cinoptions=:0
set   cursorline 	" 为光标所在行加下划线
set   completeopt=longest,menuone
set   noexpandtab
set   fileencodings=utf-8,gb2312,gbk,gb18030 " 使用utf-8或gbk等编码打开文件
set   fileformat=unix
set   foldenable
set   foldmethod=marker " 代码折叠
set   guioptions-=T
set   guioptions-=m
set   guioptions-=r
set   guioptions-=l
set   helpheight=10
set   helplang=cn 	" 帮助系统设置为中文
set   hidden
set   history=100 	" 历史记录保留100条
set   hlsearch
set   ignorecase 	" 检索时忽略大小写
set   incsearch
set   laststatus=2 	" 指定何时显示状态行
"                            " 0 永远没有
"                            " 1 只有分割窗口时(默认值)
"                            " 2 总是存在
set   mouse=a 		" 可以使用鼠标
set   number 		" 显示行号
set   pumheight=10
set   ruler
set   scrolloff=5
set   shiftwidth=4
set   showcmd
set   smartindent	" 开启智能缩进，它不像cindent那样完美支持c文件的缩进，但对于未知类型文件的缩进，还是有帮助的
set   smartcase
set   tabstop=4 	" 制表符为4
set   termencoding=utf-8
set   textwidth=80
set   whichwrap=h,l
set   wildignore=*.bak,*.o,*.e,*~
set   wildmenu
set   wildmode=list:longest,full
set   nowrap 		" 禁止文字自动换行
" }}}1
" --------------------------------------------------------------------
" AUTO COMMANDS:
" --------------------------------------------------------------------
"  {{{1
autocmd BufNewFile *.c,*.cpp,*.sh,*.py,*.java exec ":call SetTitle()"                                                                                       
"新建.py
"定义函数SetTitle，自动插入文件头
func SetTitle()
		"如果文件类型为.c或者.cpp文件
        if (&filetype == 'c' || &filetype == 'cpp')
                call setline(1, "/*************************************************************************")  
                call setline(2, "\ @Author: wanghan")  
                call setline(3, "\ @Created Time : ".strftime("%c"))  
                call setline(4, "\ @File Name: ".expand("%"))  
                call setline(5, "\ @Description:")  
                call setline(6, " ************************************************************************/")  
                call setline(7,"")  
        endif
		"如果文件类型为.sh文件
        if &filetype == 'sh'  
                call setline(1, "\#!/bin/bash")
                call setline(2, "\# Author: wanghan")
                call setline(3, "\# Created Time : ".strftime("%c"))
                call setline(4, "\# File Name: ".expand("%"))
                call setline(5, "\# Description:")
                call setline(6,"")
        endif
        "如果文件类型为.py文件
        if &filetype == 'python'
                call setline(1, "\#!/usr/bin/env python")
                call setline(2, "\# -*- coding=utf8 -*-")
                call setline(3, "\"\"\"")
                call setline(4, "\# Author: wanghan")
                call setline(5, "\# Created Time : ".strftime("%c"))
                call setline(6, "\# File Name: ".expand("%"))
                call setline(7, "\# Description:")
                call setline(8, "\"\"\"")
                call setline(9,"")
        endif
		"如果文件类型为.java文件
        if &filetype == 'java'  
                call setline(1, "//coding=utf8")  
                call setline(2, "/**")  
                call setline(3, "\ *\ @Author: wanghan")  
                call setline(4, "\ *\ @Created Time : ".strftime("%c"))  
                call setline(5, "\ *\ @File Name: ".expand("%"))  
                call setline(6, "\ *\ @Description:")  
                call setline(7, "\ */")  
                call setline(8,"")  
        endif
endfunc
" }}}1
" --------------------------------------------------------------------
" SYSTEM SHORTCUT SETTINGS:
" --------------------------------------------------------------------
"  {{{1
" Set mapleader
let mapleader=","
" Space to command mode.
nnoremap <space> :
vnoremap <space> :
" Switching between buffers.
nnoremap <C-h> <C-W>h
nnoremap <C-j> <C-W>j
nnoremap <C-k> <C-W>k
nnoremap <C-l> <C-W>l
" }}}1
" --------------------------------------------------------------------
" PLUGINS SETTINGS:
" --------------------------------------------------------------------
" {{{1
" 启动pathogen插件管理器
execute pathogen#infect() 
" 管理vim配色
"set   background=dark " 配色主题的色系设置为dark
colorscheme solarized " 配色主题的名称设置为solarized
" 配置Taglist插件
let g:Tlist_Auto_Update=1
let g:Tlist_Process_File_Always=1
let g:Tlist_Exit_OnlyWindow=1
let g:Tlist_Show_One_File=1
let g:Tlist_WinWidth=25
let g:Tlist_Enable_Fold_Column=0
let g:Tlist_Auto_Highlight_Tag=1
" 配置NERDTree插件
let Tlist_Show_One_File=1
let g:NERDTreeWinPos="right"
let g:NERDTreeWinSize=25
let g:NERDTreeShowLineNumbers=1
let g:NERDTreeQuitOnOpen=1
" 配置CrtlP插件
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'
" 配置cscope
if has("cscope")
    set csto=1
    set cst
    set nocsverb
    if filereadable("cscope.out")
        cs add cscope.out
    endif
    set csverb
endif
" Man.vim Man手册插件 这个插件是vim自带的
source $VIMRUNTIME/ftplugin/man.vim
" }}}1
" --------------------------------------------------------------------
" PLUGIN SHORTCUT SETTINGS:
" --------------------------------------------------------------------
"  {{{1
" 快捷键依赖的运行shell脚本的函数
function! RunShell(Msg, Shell)
	echo a:Msg . '...'
	call system(a:Shell)
	echon 'done'
endfunction
" ------------------
" <Fx>类型快捷键
" ------------------
nmap  <F2> :TlistToggle<cr>
nmap  <F3> :NERDTreeToggle<cr>
nmap  <F4> :MRU<cr>
nmap  <F9> :call RunShell("Generate tags", "ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .")<cr>
nmap <F10> :call RunShell("本地生成cscope文件", "bash ~/.vim/shell/create_cscope.sh")<cr>
nmap <F12> :call RunShell("Generate cscope", "cscope -Rb")<cr>:cs add cscope.out<cr>
" ------------------
" <leader>类型快捷键
" ------------------
" Cscope命令说明：
" cscope add cscope.out --- 添加cscope.out文件
" cscope find s --- 查找C语言符号，即查找函数名、宏、枚举值等出现的地方
" cscope find g --- 查找函数、宏、枚举等定义的位置，类似ctags所提供的功能
" cscope find d --- 查找本函数调用的函数
" cscope find c --- 查找调用本函数的函数
" cscope find t --- 查找指定的字符串
" cscope find e --- 查找egrep模式，相当于egrep功能，但查找速度快多了
" cscope find f --- 查找并打开文件，类似vim的功能
" cscope find i --- 查找包含本文件的文件
" ------------------------------------------------------------------
"	USAGE	:cs add {file|dir} [pre-path] [flags]
"
"	USAGE	:cs find {querytype} {name}
"		0 or s: Find this C symbol
"		1 or g: Find this definition
"		2 or d: Find functions called by this function
"		3 or c: Find functions calling this function
"		4 or t: Find this text string
"		6 or e: Find this egrep pattern
"		7 or f: Find this file
"		8 or i: Find files #including this file
nmap <leader>sa :cs add cscope.out<cr>
nmap <leader>ss :cs find s <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sg :cs find g <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sc :cs find c <C-R>=expand("<cword>")<cr><cr>
nmap <leader>st :cs find t <C-R>=expand("<cword>")<cr><cr>
nmap <leader>se :cs find e <C-R>=expand("<cword>")<cr><cr>
nmap <leader>sf :cs find f <C-R>=expand("<cfile>")<cr><cr>
nmap <leader>si :cs find i <C-R>=expand("<cfile>")<cr><cr>
nmap <leader>sd :cs find d <C-R>=expand("<cword>")<cr><cr>
",c 创建新标签
",x 删除标签
",[ 移动到前一个标签
",] 移动到下一个标签
nmap <leader>c :tabnew<cr>
nmap <leader>x :tabclose<cr>
nmap <leader>] :tabn<cr>
nmap <leader>[ :tabp<cr>
" }}}1
