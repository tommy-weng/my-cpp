#include <iostream>

class Quote {
    public:
        Quote () = default;
        Quote(const std::string &book, double sales_price ):bookNo(book), price(sales_price) { }
        std::string isbn () const { return bookNo; }
        virtual double net_price(std::size_t n) const
        { return n * price; }
        virtual ~Quote ( ) = default;
    private:
        std::string bookNo;
    protected:
        double price = 0.0;
};

class Disc_quote : public Quote {
    public:
        Disc_quote() = default;
        Disc_quote(const std::string& book, double price, std::size_t qty, double disc):
            Quote (book, price), quantity(qty), discount(disc) { }
        double net_price(std::size_t) const = 0;
    protected:
        std::size_t quantity = 0; 
        double discount = 0.0; 
};

class Bulk_quote : public Disc_quote {
    public:
        Bulk_quote() = default;
        Bulk_quote(const std::string& book, double price, std::size_t qty, double disc):
            Disc_quote(book, price, qty, disc) { }
        double net_price(std::size_t) const override;
};

double Bulk_quote::net_price(std::size_t n) const
{
    if (n > quantity)
    {
        return (n - quantity) * price + quantity * price * discount;
    }
    else
    {
        return n * price * discount;    
    }
}

int main()
{
    // Disc_quote dq("1001x", 39.00, 10, 0.9);
    Bulk_quote bq("1002x", 45.00, 20, 0.8);

    std::cout << bq.isbn() << ": " << bq.net_price(30) << std::endl;
    return 0;
}
