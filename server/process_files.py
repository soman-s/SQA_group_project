

class ProcessFiles:    
    def get_daily_transactions(self):
        daily_transactions = []
        with open('../Code/log_files/daily_transactions.etf', 'r') as file:
            for line in file:
                daily_transactions.append(line.strip())
        return daily_transactions
    def update_files(self):
        pass