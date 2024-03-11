

def pad_end_file(total_chars:int)->str:
    ending=word = "END" + " " * (total_chars - len("END"))
    return ending
