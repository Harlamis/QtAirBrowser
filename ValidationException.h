#ifndef VALIDATIONEXCEPTION_H
#define VALIDATIONEXCEPTION_H
#include <exception>
#include <QString>

class ValidationExcpetion : public std::exception {
    QString message;
    QByteArray m_utf8Message;
public:
    explicit ValidationExcpetion(const QString& msg)
        : message(msg) {
        m_utf8Message = message.toUtf8();
    };
    QString getMessage() const {return message;};
    const char* what() const noexcept override {
        return m_utf8Message.constData();
    }
};
#endif // VALIDATIONEXCEPTION_H
