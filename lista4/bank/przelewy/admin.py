from django.contrib import admin

from .models import Transfer, UnconfirmedTransfer
from .utils import confirm_transfer

def confirm_transfers(modeladmin, request, queryset):
    for t in queryset:
       confirm_transfer(t)

confirm_transfers.short_description = 'Zatwierdź'

admin.site.register(Transfer)

class UnconfirmedTransferAdmin(admin.ModelAdmin):
    actions = [confirm_transfers]

admin.site.register(UnconfirmedTransfer, UnconfirmedTransferAdmin)
