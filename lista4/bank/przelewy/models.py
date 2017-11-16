from django.db import models
from django.utils import timezone
from .utils import render_value

class Transfer(models.Model):
    source = models.CharField(max_length=200)
    target = models.CharField(max_length=200)
    amount = models.DecimalField(max_digits=20, decimal_places=15)
    created_date = models.DateTimeField(default=timezone.now)

    def __str__(self):
        return '{} -> {}, {} zł, {}'.format(self.source, self.target, self.amount, render_value(self.created_date))

class UnconfirmedTransfer(models.Model):
    source = models.CharField(max_length=200)
    target = models.CharField(max_length=200)
    amount = models.DecimalField(max_digits=20, decimal_places=15)

    def __str__(self):
        return '{} -> {}, {} zł'.format(self.source, self.target, self.amount)

