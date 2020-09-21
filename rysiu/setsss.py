digits = set("2709")
text = input()
text_set = set(text)
if digits & text_set:
    print(text)
