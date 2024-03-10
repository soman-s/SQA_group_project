from process_files import ProcessFiles
from transactions import Transactions



if __name__ == '__main__':

    transaction = Transactions()
    codes = {"01":transaction.create_user()}
    processFiles = ProcessFiles()
    daily_transactions = processFiles.get_daily_transactions()
    for transaction in daily_transactions:
        if transaction[0:2] in codes == "01":
            transaction.create_user()

    print("in here")
    
    

