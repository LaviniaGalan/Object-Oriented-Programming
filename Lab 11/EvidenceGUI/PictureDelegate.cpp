#include "PictureDelegate.h"

PictureDelegate::PictureDelegate(QWidget* parent)
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

	if (index.column() != INDEX_OF_PHOTOGRAPH)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	QString evidence = index.model()->data(index, Qt::EditRole).toString();

	if (evidence.contains("fingerprint"))
	{
		QPixmap pixMap("Fingerprint.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (evidence.contains("shoeprint"))
	{
		QPixmap pixMap("Shoeprint.jpeg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (evidence.contains("gun"))
	{
		QPixmap pixMap("Gun.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (evidence.contains("ADN"))
	{
		QPixmap pixMap("ADN.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == INDEX_OF_PHOTOGRAPH)
	{
		return QSize(250, 100);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
