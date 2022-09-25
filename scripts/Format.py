#-----------------------------------------------------------------------       
# The functions in this module have been adapted from functions used
# in the Cordet FW Editor for processing DB text.
#-----------------------------------------------------------------------       
       
import os
import re
import json

from Config import specItems

# Regex pattern for text emphasis markdown
# Bold is: '**...**'
# Underline is: '++...++'
# Italicize is: '__...__'
# Teletype is: '``...``'
pattern_emphasis = re.compile('(\*\*)(.+?)(\*\*)|(\+\+)(.+?)(\+\+)|(__)(.+?)(__)|(``)(.+?)(``)')     

# Regex pattern for internal references to specification items as they
# are stored in the database (e.g. '#iref:1234')
pattern_db = re.compile('#(iref):([0-9]+)')    

# Regex expression for bulleted lists in database text
pattern_bullets = re.compile('((\n^-\s.+$)+)', re.MULTILINE)    

# Regex patterns for internal references to specification items as they are
# rendered in edit representation (e.g. '#cat:dom:name').
# One such regex pattern is created for each project holding the categories
# for that project.
cats = 'AdaptPoint|DataItem|DataItemType|InCommand|Packet|PacketPar|DerPacket|EnumType|EnumValue|Model|OutComponet|Service'
pattern_edit = re.compile('#('+cats+'):([a-zA-Z0-9_]+):([a-zA-Z0-9_]+)')
    
# ----------------------------------------------------------------------
# Format string for output to a Latex text file
def frmt_string(s):
    replacements = [['\r\n', ' \\newline '],
                ['\r', ' \\newline '],
                ['\n', ' \\newline '],
                ['%', '\\%'],
                ['&', '\\&'],
                ['#', '\\#'],
                ['^', "\\textasciicircum "],
                ['~', "\\textasciitilde "],
                ['_', "\\_"]]
    for old, new in replacements:
       s = s.replace(old, new)    
    return s

# ----------------------------------------------------------------------
def emphasis_to_latex(match):
    if match.group(1) != None:
        return '\\textbf{'+match.group(2)+'}'
    elif match.group(4) != None:
        return '\\underline{'+match.group(5)+'}'
    elif match.group(7) != None:
        return '\\textit{'+match.group(8)+'}'
    elif match.group(10) != None:
        return '\\texttt{'+match.group(11)+'}'

# ----------------------------------------------------------------------
def bulleted_list_to_latex(match):
    s1 = match.group(1).replace('\n','')
    s2 = s1.replace('\r','')
    bullet_items = s2.split('- ')
    s_html = '\\begin{itemize}'
    for i, bullet_item in enumerate(bullet_items): 
        if i>0:
            s_html = s_html + '\\item '+bullet_item
    return s_html + '\\end{itemize}'+' \ ' # Backslash adds a space

# ----------------------------------------------------------------------
def markdown_to_latex(s):
    s_emph = pattern_emphasis.sub(emphasis_to_latex, s)
    s_bullets = pattern_bullets.sub(bulleted_list_to_latex, s_emph)
    return s_bullets
    

# ----------------------------------------------------------------------
#  The argument string is a text field read from a database export which 
#  contains markdown text and internal references.
#  Internal references in the form #cat:domain:name are converted to a
#  category-specific form and special latex characters are escaped.
#  Markdown text is converted to latex.
def convertEditToLatex(s):
    # Function called by sub() to replace occurrences of the #iref:n regex pattern """
    def edit_to_latex(match):
        if match.group(1) == 'Model':
            return '\ref{fig:'+match.group(3)
        else:
            return match.group(2)+':'+match.group(3)
    
    s_ref = pattern_edit.sub(edit_to_latex, s)
    s_md = markdown_to_latex(s_ref)
    return frmt_string(s_md)
    
