<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Installation auf Microsoft Hyper-V unter Windows Server 2012 R2 | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="install.php" title="Teil&nbsp;1.&nbsp;Installation"><link rel="prev" href="install-virtual-vmware-install.php" title="5.3. Installation des Intranators"><link rel="next" href="install-virtual-hyperv2012-install.php" title="6.2. Installation des Intranators">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="install-virtual-hyperv2012.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="install-virtual-hyperv2012.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">6. Kapitel - Installation auf Microsoft Hyper-V unter Windows Server 2012 R2</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="install-virtual-vmware-install.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;1.&nbsp;Installation</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="install-virtual-hyperv2012-install.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="install-virtual-hyperv2012"></a>6. Kapitel - Installation auf Microsoft Hyper-V unter Windows Server 2012 R2</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="install-virtual-hyperv2012.php#install-virtual-hyperv2012-config">6.1. Konfiguration der virtuellen Maschine</a></span></dt><dt><span class="sect1"><a href="install-virtual-hyperv2012-install.php">6.2. Installation des Intranators</a></span></dt></dl></div><a class="indexterm" name="install-virtual-hyperv2012-install1"></a><p>Das Virtualisierungssystem Hyper-V ist Bestandteil des Windows Server 2012 R2 von
        Microsoft und kann als Rolle in diesem aktiviert werden. </p><p>Zus&auml;tzlich ist auch der dauerhaft kostenlose Microsoft Hyper-V Server 2012 R2 erh&auml;ltlich.
        Dieser kann aber nur &uuml;ber Kommandozeile und Powershell bedient werden, was Konfiguration und
        Wartung deutlich erschwert. Wir k&ouml;nnen diesen daher nur erfahrenen Windows-Administratoren
        mit umfassenden Kenntnissen in der Bedienung per Kommandozeile empfehlen und bieten daf&uuml;r
        auch keinen Support an. Wir empfehlen daher f&uuml;r Virtualisierung mit Hyper-V den Windows
        Server 2012 R2 zu verwenden.</p><p>Der Intranator Server enth&auml;lt von Haus aus alle Treiber und Programme, die f&uuml;r den
        zuverl&auml;ssigen Betrieb auf Microsoft Hyper-V unter Windows Server 2012 R2 n&ouml;tig sind. Eine
        zus&auml;tzliche Installation der Integrationsdienste oder anderer Treiber oder Programme ist
        nicht notwendig oder m&ouml;glich.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Hyper-V bietet keine M&ouml;glichkeit PCI-Ger&auml;te wie Netzwerkkarten direkt an eine VM
            durchzureichen. Daher raten wir dringend davon ab, einen damit virtualisierten
            Intranator ohne zus&auml;tzliche Hardware-Firewall einzusetzen. Weitere Informationen dazu
            finden Sie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="install-virtual.php#install-virtual-real-directnic">Abschnitt&nbsp;4.1.3, &#8222;Kontakt mit ungefilterten Netzwerkpaketen&#8220;</a>.</p></td></tr></table></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="install-virtual-hyperv2012-config"></a>6.1. Konfiguration der virtuellen Maschine</h2></div></div></div><p>Gehen Sie f&uuml;r die Installation einer virtuellen Maschine wie folgt vor:</p><div class="orderedlist"><ol type="1"><li><p>&Ouml;ffnen Sie den Hyper-V-Manager und klicken mit der rechten Maustaste auf die
                    gew&uuml;nschte Hyper-V-Instanz. W&auml;hlen Sie
                        <span class="guimenu">Neu&nbsp;&gt;&nbsp;Festplatte...</span>.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-disk01.png"></div></li><li><p>W&auml;hlen Sie das Format <span class="guimenuitem">VHDX</span>.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-disk02.png"></div></li><li><p>W&auml;hlen Sie eine virtuelle Festplatte mit <span class="guimenuitem">Fester
                        Gr&ouml;&szlig;e</span>.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-disk03.png"></div></li><li><p>Geben Sie der virtuellen Festplatte einen zur zuk&uuml;nftigen VM passenden Namen. </p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-disk04.png"></div></li><li><p>Weisen Sie dem Intranator eine Festplatte von mindestens 40 GB zu. Wird der
                    Intranator nur zum Scannen von E-Mails und als HTTP-Proxyserver eingesetzt,
                    reichen diese 40 GB im Normalfall auch aus. Nur wenn umfangreiche Statistikdaten
                    f&uuml;r viele Benutzer l&auml;ngerfristig gespeichert werden sollen, wird mehr Speicher
                    ben&ouml;tigt.</p><p>Werden E-Mails oder Groupwaredaten dauerhaft auf dem Intranator abgelegt, wird
                    mehr Festplattenplatz ben&ouml;tigt. Als Faustformel gilt Folgendes: ( Gesamtes
                    E-Mail-Volumen aller Benutzer + Statistikdaten) * (Anzahl auf dem System
                    gespeicherter Backups&auml;tze + 2) + 20 GB. Die Anzahl auf dem System gespeicherter
                    Backups&auml;tze betr&auml;gt dabei mindestens 1, empfohlen wird 2.</p><p>Kalkulieren Sie immer etwas Reserve ein, da ein Vergr&ouml;&szlig;ern der Festplatte im
                    Betrieb derzeit nicht unterst&uuml;tzt wird.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-disk05.png"></div></li><li><p>Legen Sie die virtuelle Festplatte fertig an.</p></li><li><p>Klicken mit der rechten Maustaste auf die gew&uuml;nschte Hyper-V-Instanz und
                    w&auml;hlen <span class="guimenu">Neu&nbsp;&gt;&nbsp;Virtueller Computer...</span>.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-vm01.png"></div></li><li><p>Geben Sie der VM einen Namen.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-vm02.png"></div></li><li><p>W&auml;hlen Sie Generation 1.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-vm03.png"></div></li><li><p>Weisen Sie der VM ausreichend Arbeitsspeicher zu. Verwenden Sie mindestens 2
                    GB. Deaktivieren Sie die Funktion <span class="guimenuitem">Dynamischer
                        Arbeitsspeicher</span>.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-vm04.png"></div></li><li><p>Verbinden Sie die VM mit dem virtuellen Switch der mit dem lokalen Netzwerk
                    verbunden ist.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-vm05.png"></div></li><li><p>Weisen Sie die vorher erstellte virtuelle Festplatte zu.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-vm06.png"></div></li><li><p>Schlie&szlig;en Sie das Anlegen der VM ab.</p></li><li><p>Klicken Sie die neue VM mit der rechten Maustaste an und &ouml;ffnen die
                        <span class="guimenu">Einstellungen</span>.</p></li><li><p>Lassen Sie die VM immer automatisch starten damit die VM immer verf&uuml;gbar
                    ist.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-options01.png"></div></li><li><p>Lassen Sie die VM bei Herunterfahren des Hyper-V-Servers immer herunterfahren.
                    Dies beugt Problemen durch Zeitspr&uuml;nge vor. </p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-options02.png"></div></li><li><p>Erh&ouml;hen Sie die Anzahl der zugewiesenen Prozessorcores je nach verf&uuml;gbaren
                    Ressourcen. Diese Einstellung k&ouml;nnen Sie auch sp&auml;ter noch an den Bedarf
                    anpassen.</p><div class="mediaobject"><img src="../images/install/hyperv2012/hyperv-options03.png"></div></li></ol></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="install-virtual-vmware-install.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="install.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="install-virtual-hyperv2012-install.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">5.3. Installation des Intranators&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;6.2. Installation des Intranators</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>