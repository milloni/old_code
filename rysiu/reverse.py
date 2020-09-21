text = input("Text input: ")
output_text = ""
i = 0
while i < len(text):
    if text[i] != "\t":
        output_text += text[i]
    else:
        output_text += " " * 4
    i += 1
print("Output text is: ")
print(output_text)
