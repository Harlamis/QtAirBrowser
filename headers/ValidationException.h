#ifndef VALIDATIONEXCEPTION_H
#define VALIDATIONEXCEPTION_H
#include <exception>
#include <QString>

/// @brief Custom exception for validation errors.
/// Thrown when user input is invalid or database operations fail.
class ValidationException : public std::exception {
    QString message;
    QByteArray m_utf8Message;
public:
    /// @brief Constructs exception with a message.
    /// @param msg The error message.
    explicit ValidationException(const QString& msg)
        : message(msg) {
        m_utf8Message = message.toUtf8();
    };

    /// @brief Gets the error message as QString.
    QString getMessage() const {return message;};

    /// @brief Standard std::exception override.
    const char* what() const noexcept override {
        return m_utf8Message.constData();
    }
};
#endif // VALIDATIONEXCEPTION_H
