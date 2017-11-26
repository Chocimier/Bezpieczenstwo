from decimal import Decimal, InvalidOperation
from django.template import Context, Template

def build_unconfirmed_transfer(request):
    from .models import UnconfirmedTransfer
    transfer = UnconfirmedTransfer()
    try:
        transfer.source = request.POST['source']
        transfer.target = request.POST['target']
        transfer.amount = Decimal(request.POST['amount'])
    except (KeyError, InvalidOperation):
        return None
    if transfer.source != request.user.username or transfer.target == '' or transfer.amount <= 0:
        return None
    transfer.save()
    return transfer

def build_transfer(request):
    from .models import UnconfirmedTransfer
    try:
        unconfirmed_id = request.POST['id']
        unconfirmed_transfer = UnconfirmedTransfer.objects.get(id=unconfirmed_id)
    except (UnconfirmedTransfer.DoesNotExist, KeyError):
        return None
    if unconfirmed_transfer.source != request.user.username:
        return None
    return confirm_transfer(unconfirmed_transfer)

def confirm_transfer(unconfirmed_transfer):
    from .models import Transfer
    transfer = Transfer()
    transfer.source = unconfirmed_transfer.source
    transfer.target = unconfirmed_transfer.target
    transfer.amount = unconfirmed_transfer.amount
    transfer.save()
    unconfirmed_transfer.delete()
    return transfer

def render_value(value):
    return Template('{{ v }}').render(Context({'v': value}))
