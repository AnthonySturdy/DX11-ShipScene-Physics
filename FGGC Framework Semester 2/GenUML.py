                  # UML Content Generator #
#############################################################
#   PLACE THIS SCRIPT IN THE FOLDER WITH ALL SOURCE FILES   #
#    IF SOURCE FILES ARE SPLIT INTO FOLDERS, MAKE A COPY    #
#                 OF FILES IN A NEW FOLDER                  #
#                                                           #
#   * Doesn't work on classes where everything is in .h,    #
#        only works with standard .h files containing       #
#         Variables, Prototypes and Inline functions        #
#############################################################

import glob

def main():
    # For each header file in directory, call ProcessFile()
    for file in glob.glob("*.h"):
        ProcessFile(file)

def ProcessFile(fileName):
    print("Processing " + fileName)
    file = open(fileName, "r")
    writeFile = open("GenUML_" + fileName + ".txt", "w+")

    access = ' '        # ' ' = Don't process, '-' = private, '+' = public, '#' = protected

    includes = []
    variables = []
    functions = []

    # Loop through line by line
    for line in file:
        if "public:" in line:
            access = '+'
            continue
        elif "private:" in line:
            access = '-'
            continue
        elif "protected:" in line:
            access = '#'
            continue
        elif "};" in line:
            access = ' '
            continue
        elif "include \"" in line:
            includes.append(line)
            continue
        elif "include\"" in line:
            includes.append(line)
            continue
        
        # If line is to be processed
        if access != ' ':
            strippedLine = line
            # Strip unneeded content from end of line
            # e.g. will remove '= 25' from 'int x = 25;'
            #      or '{ return x; } from 'int GetX() { return x; }'
            if "{" in strippedLine:
                strippedLine = strippedLine.split('{')[0]
            if "=" in strippedLine:
                strippedLine = strippedLine.split('=')[0]
            if "//" in strippedLine:
                strippedLine = strippedLine.split("//")[0]

            # Skip if string is empty
            if strippedLine == "" or strippedLine.isspace():
                continue;

            # Remove other bits
            strippedLine = strippedLine.replace(";", "")
            strippedLine = strippedLine.replace("\n", "")
            strippedLine = strippedLine.replace("\t", "")
            strippedLine = strippedLine.replace("const", "")
            strippedLine = strippedLine.replace("static", "")
            strippedLine = strippedLine.replace("inline", "")

            # Remove multiple whitespace
            strippedLine = " ".join(strippedLine.split())

            # Split string into array
            lineArray = strippedLine.split(' ')

            # Remove variable names from arguments (not needed)
            for i in range(0, len(lineArray)):
                if "," in lineArray[i]:
                    lineArray[i] = ","
                if ")" in lineArray[i] and "(" not in lineArray[i]:
                    lineArray[i] = ")"

            #Re-arrange type and name, add the :
            if "(" not in lineArray[0]:
                lineArray.append(lineArray.pop(0))
                lineArray.insert(-1, " : ")

            # Create final string
            finalString = access + ' ' + ''.join(lineArray)

            # Determine which array to add final string to
            if "(" in finalString:
                functions.append(finalString)
            else:
                variables.append(finalString)
            
    for x in includes:
        writeFile.write(x)
    
    writeFile.write("\n")

    for x in variables:
        writeFile.write(x + "\n")

    writeFile.write("\n")

    for x in functions:
        writeFile.write(x + "\n")

    file.close()
    writeFile.close()
            
            

if __name__ == "__main__":
    main()